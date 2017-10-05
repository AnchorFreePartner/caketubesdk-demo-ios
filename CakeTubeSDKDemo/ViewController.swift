//
//  ViewController.swift
//  CakeTubeSDKDemo
//
//  Created by Igor Glotov on 10/3/17.
//  Copyright © 2017 Anchorfree Inc. All rights reserved.
//

import UIKit
import CakeTubeSDK

class ViewController: UIViewController, CountryControllerDelegate {
    
    @IBOutlet weak var loginButton: UIButton!
    @IBOutlet weak var connectButton: UIButton!
    @IBOutlet weak var changeCountryButton: UIButton!
    @IBOutlet weak var loginStatus: UILabel!
    @IBOutlet weak var connectionStatus: UILabel!
    @IBOutlet weak var countryLabel: UILabel!
    @IBOutlet weak var trafficLimitLabel: UILabel!
    @IBOutlet weak var trafficStatsLabel: UILabel!
    
    var isLoggedIn : Bool {
        get {
            return CakeTube.instance().isLoggedIn()
        }
    }
    
    var isVpnConnected : Bool {
        get {
            return CakeTube.instance().vpnStatus == .connected
        }
    }
    
    var location : CTServerLocation? {
        get {
            return CakeTube.instance().getServer()
        }
        set {
            CakeTube.instance().setServer(newValue)
        }
    }
    
    var statusString: String {
        switch CakeTube.instance().vpnStatus {
        case .disconnecting:
            return "Disconnecting"
        case .connecting:
            return "Connecting"
        case .connected:
            return "Connected"
        case .invalid, .undefined, .disconnected:
            return "Disconnected"
        }
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        self.updateUi()
        NotificationCenter.default.addObserver(forName: NSNotification.Name.CTVPNStatusDidChange, object: nil, queue: OperationQueue.main) { [unowned self] (notifictaion) in
            self.updateUi()
            if self.isVpnConnected {
                self.updateTrafficStats()
                self.updateTrafficLimits()
            }
        }
    }
    
    @IBAction func toggleLogin(_ sender: UIButton) {
        if self.isLoggedIn {
            CakeTube.instance().logout { [unowned self] (e) in
                if let ex = e {
                    print("Logout error: \(ex)")
                } else {
                    print("Logout success")
                }
                
                self.updateUi()
            }
        } else {
            CakeTube.instance().login(with: CTAuthMethod.anonymous(), completion: { (user, e) in
                if let ex = e {
                    print("Login error: \(ex)")
                } else {
                    print("Login success")
                }
                
                self.updateUi()
            })
        }
    }
    
    @IBAction func toggleConnect(_ sender: UIButton) {
        if !self.isVpnConnected {
            CakeTube.instance().startVPN { (location, e) in
                if let ex = e {
                    print("Start VPN error: \(ex)")
                } else {
                    print("Start VPN success, country: \(location?.country ?? "n/a")")
                }
            }
        } else {
            CakeTube.instance().stopVPN { (e) in
                if let ex = e {
                    print("Stop VPN error: \(ex)")
                } else {
                    print("Stop VPN success")
                }
            }
        }
    }
    
    @IBAction func changeCountry(_ sender: UIButton) {
        let controller = self.storyboard?.instantiateViewController(withIdentifier: "CountryController") as! CountryController
        controller.currentLocation = self.location
        controller.delegate = self
        self.present(controller, animated: true, completion: nil)
    }
    
    func updateUi() {
        self.loginButton.setTitle(self.isLoggedIn ? "Log out" : "Log in", for: .normal)
        self.loginStatus.text = self.isLoggedIn ? "Logged in" : "Logged out"
        self.connectButton.setTitle(self.isVpnConnected ? "Stop VPN" : "Start VPN", for: .normal)
        self.connectionStatus.text = self.statusString
        self.countryLabel.text = self.location?.country ?? "Optimal"
    }
    
    @objc func updateTrafficStats() {
        if !isVpnConnected { return }
        CakeTube.instance().trafficStats { (counters, e) in
            if let ex = e {
                print("trafficStats error: \(ex)")
                // NOTE: Counters may not be ready immediately after connection
                self.perform(#selector(self.updateTrafficStats), with: nil, afterDelay: 5.0)
                return
            }
            
            print("trafficStats success")
            
            guard let counters = counters else { return }
        
            let ul = ByteCountFormatter.string(fromByteCount: counters.tx.int64Value, countStyle: .file)
            let dl = ByteCountFormatter.string(fromByteCount: counters.rx.int64Value, countStyle: .file)
            let string = "UL: \(ul), DL: \(dl)"
            self.trafficStatsLabel.text = string
            self.perform(#selector(self.updateTrafficStats), with: nil, afterDelay: 5.0)
        }
    }
    
    func updateTrafficLimits() {
        CakeTube.instance().remainingTraffic { (remainingTraffic, e) in
            if let ex = e {
                print("remainingTraffic error: \(ex)")
                return;
            }
            
            print("remainingTraffic success")
            
            guard let traffic = remainingTraffic else { return }
            if let trafficLimit = traffic.trafficLimit {
                if trafficLimit == -1 {
                    self.trafficLimitLabel.text = "Traffic is unlimited"
                } else {
                    var string : String = ByteCountFormatter.string(fromByteCount: traffic.trafficRemaining?.int64Value ?? 0, countStyle: .file)
                    string += " of "
                    string += ByteCountFormatter.string(fromByteCount: trafficLimit.int64Value, countStyle: .file)
                    string += " remaining"
                    self.trafficLimitLabel.text = string
                }
            }
        }
    }

    func locationChanged(_ newLocation: CTServerLocation?) {
        self.location = newLocation
        updateUi()
    }
}

