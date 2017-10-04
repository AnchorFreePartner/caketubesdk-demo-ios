//
//  CountryController.swift
//  CakeTubeSDKDemo
//
//  Created by Igor Glotov on 10/3/17.
//  Copyright © 2017 Anchorfree Inc. All rights reserved.
//

import UIKit
import CakeTubeSDK

protocol CountryControllerDelegate {
    func locationChanged(_ newLocation: CTServerLocation?)
}
class CountryController: UITableViewController {
    var currentLocation : CTServerLocation?
    var delegate : CountryControllerDelegate?
    var locationsList: [CTServerLocation]?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        UIApplication.shared.isNetworkActivityIndicatorVisible = true

        CakeTube.instance().availableServers { [weak self] (locations, e) in
            UIApplication.shared.isNetworkActivityIndicatorVisible = false
            
            if let ex = e {
                print("Countries error: \(ex)")
            } else {
                print("Countries success")
            }
            
            self?.locationsList = locations
            self?.tableView.reloadData()
        }
    }

    // MARK: - Table view data source

    override func numberOfSections(in tableView: UITableView) -> Int {
        // #warning Incomplete implementation, return the number of sections
        return 1
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        // #warning Incomplete implementation, return the number of rows
        return self.locationsList?.count ?? 0
    }

    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "DefaultCell", for: indexPath)
        guard let locationsList = self.locationsList else { return cell }
        let location = locationsList[indexPath.row]
        var labelString: String = location.country as String!
        if self.currentLocation?.country == location.country {
            labelString += " (selected)"
        }
        cell.textLabel?.text = labelString
        return cell
    }

    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        tableView.deselectRow(at: indexPath, animated: true)
        guard let locationsList = self.locationsList else { return }
        delegate?.locationChanged(locationsList[indexPath.row])
        dismiss(animated: true, completion: nil)
    }
}
