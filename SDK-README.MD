# CakeTubeSDK for iOS & macOS

Download latest SDK: 
- [CakeTubeSDK for iOS](https://firebasestorage.googleapis.com/v0/b/web-portal-for-partners.appspot.com/o/products%2FCakeTubeSDK-iOS.framework.zip?alt=media)
- [CakeTubeSDK for macOS](https://firebasestorage.googleapis.com/v0/b/web-portal-for-partners.appspot.com/o/products%2FCakeTubeSDKmacOS.framework.zip?alt=media)

CakeTube for iOS & macOS (The SDK) is a part of AnchorFree SDK. It contains client-side libraries and server-side applications needed to implement custom VPN infrastructure.

The SDK provides API to authorize client users and gives them an ability to connect to backend VPN services.

# Prerequisites

* Requires iOS 9+ or macOS 10.12+
* XCode 9

# Setup

### Creating application

To start application development, you need to create a XCode application project. 

At the end of this step you will have a new target: 
* **Application** target

### Configure Build Settings and integrate CakeTubeSDK

For **Application** target do the following

Add following system frameworks to your project dependencies:
- For iOS: CakeTubeSDK.framework
- For macOS: CakeTubeSDKmacOS.framework
- If it's a Swift project, also add this framework to Embedded binaries

### Configure App ID

Go to [Apple Developer Portal](https://developer.apple.com/) and create (if not yet created) an application ID under *Identifiers > App IDs* section.

Also, enable following services for both IDs:

* Personal VPN

### Enabling Capabilities

For both, **Application**  and **Network Extension** targets, go to *Project > Capabilities* and Enable the following capabilities:

* Personal VPN

> **NOTE:** Make sure that **.entitlement** is added to the project

# Start using CakeTubeSDK

### Configure CakeTubeSDK

To start using the SDK, you need to import `import CakeTubeSDK` for iOS or `import CakeTubeSDKmacOS` to your file under the application target.

To initialize SDK do the following:

    import CakeTubeSDK // or CakeTubeSDKmacOS :)

    CakeTube.instance().configure(CTConfig.create { (c) in
        c.baseUrl = "https://backend.northghost.com"
        c.carrierId = "afdemo"
        c.vpnProtocol = .ikEv2
        c.vpnProfileName = "My Awesome Application"
    })

The best place to put initialization code is you AppDelegate's `application:didFinishLaunchingWithOptions:`.

After SDK is initialized, you need to login to be able to start VPN. If you are using OAuth authentication, provide your own OAuth dialogs UI and receive OAuth access token. Login example with OAuth token:

    CakeTube.instance().login(with: CTAuthMethod.oAuth("my_access_token"), completion: { (user, e) in
        // Handle result
    })

For anonymous login, use CTAuthMethod.anonymous()
See `CTAuthMethod` reference for more authentication methods.

### Connecting VPN and obtaining status

To connect VPN use CakeTube function `startVpn`. When VPN is started or error occured, completion will be called. To obtain VPN connection status you need to subscribe to default `NotificationCenter`. For example:

    NotificationCenter.default.addObserver(forName: NSNotification.Name.CTVPNStatusDidChange, object: nil, queue: OperationQueue.main) { [unowned self] (notifictaion) in
            // VPN status changed, see CakeTube.instance().vpnStatus for exact status value
            self.updateUi()
        }
    }

When you receive notification, get updated VPN status from `CakeTube.instance().vpnStatus` status property and handle this status as designed by your app.

### Error Handling

Most of `CakeTube` calls are accepting completion blocks with errors. If an error occurs, you will receive non-nil `NSError` object with an explanation. Errors could be handled by code, that is defined in `CTCakeTubeVPNErrorCode` or `CTCakeTubeApiErrorCode`. In some cases, there is NSUnderlyingError instance inside NSError. See *CakeTube.h* for more info.

# API Documentation

### CakeTube

`+ (CakeTube *)instance;`
`- (void)configure:(CTConfig *)config;`

CakeTube class is a singleton. Use CTConfig object instance to initialize CakeTube. The fastest way to create CTConfig object instance is to use `CTConfig.create { (c) in ... }`.

`- (BOOL)isLoggedIn;`
Checks if the user is logged in.

`- (void)loginWithMethod:(CTAuthMethod *)method completion:(nullable CTLoginCompletion)completion;`
Login and obtain CTUserProfile object that describes CakeTube VPN user.

`- (void)startVPN:(nullable CTStartVPNCompletion)completion;`
Starts VPN with completion. During VPN start iOS / macOS may ask for VPN permission from the user. Callback provides `CTServerLocation` instance that describes server user connected to.

`- (void)stopVPN:(nullable CTDefaultCompletion)completion;`
Stops current VPN session.

`- (void)removeVPNProfile:(nullable CTDefaultCompletion)completion;`
Remove VPN profile. Used to troubleshoot VPN issues.

`- (void)subscriberInfo:(nullable CTSubscriberCompletion)completion;`
Get currently logged in CTUserProfile instance

`- (void)availableServers:(nullable CTServersCompletion)completion;`
Retrieve a list of the servers available to connect to

`- (void)trafficStats:(nullable CTCountersCompletion)completion;`
Get traffic I/O stats from current session in bytes

`- (void)checkVpnIsEnabled:(nullable CTVpnStatusCompletion)completion;`
Deprecated: Checks if VPN is enabled by asking backend. Alwauys use vpnStatus property to get actual status information.

`- (void)remainingTraffic:(nullable CTRemainingTrafficCompletion)completion;`
Retrieve current user's traffic limits.

`- (void)logout:(nullable CTDefaultCompletion)completion;`
Sign out current user

`- (void)checkPurchaseWithReceipt:(NSString *)receipt completion:(nullable CTPurchaseCompletion)completion;`
Validates purchase with backend. `receipt` is base64 encoded string of receipt data.

`- (void)setServer:(nullable CTServerLocation *)location;`
 Sets server location. If VPN is already connected, this method does not reconnect VPN to a new server. `location` - Server location, obtained with `[CakeTube getServers:]` or `[CTServerLocation optimal]`. `nil` value means the location will be optimal.

`- (nullable CTServerLocation *)getServer;`
Gets current server location. `nil` value means the location will be optimal.

`- (nullable NSString *)accessToken;`
Provides access token user signed in with (CakeTube backend token).

### CTAuthMethod

`+ (instancetype)anonymous;`  
Default auth method that does not require any authentication.

`+ (instancetype)OAuth:(NSString *)accessToken;`  
Most popular OAuth authentication method. OAuth flow should be implemented by your application. After finishing OAuth flow and obtaining OAuth access token, provide it to this factory.

`+ (instancetype)facebook:(NSString *)accessToken;`  
Authenticate with Facebook SDK.

`+ (instancetype)google:(NSString *)accessToken;`  
Authenticate with Google SDK.

`+ (instancetype)twitter:(NSString *)accessToken;`  
Authenticate with Twitter SDK.

`+ (instancetype)github:(NSString *)accessToken;`  
Authenticate with GitHub SDK.

`+ (instancetype)firebase:(NSString *)accessToken;`  
Authenticate with Firebase SDK.

`+ (instancetype)custom:(NSString *)methodName token:(NSString *)accessToken;`  
Custom auth. If you are using custom authentication scheme, use this method.

### Common objects

### CTConfig

`CTConfig` is a class that configures `CakeTube` instance. Created by `AFConfigBuilder`

`@property (strong, nonatomic) NSString *baseUrl;`  
This is a Host URL of the primary server. Provided by Anchorfree Inc.

`@property (strong, nonatomic) NSString *carrierId;`  
This is your unique service identifier. Provided by Anchorfree Inc.

`@property (nonnull, strong, nonatomic) NSString *vpnProfileName;`
The name of your VPN profile, visible in iOS Settings > VPN section.

`@property (nonatomic) CTVPNProtocol vpnProtocol;`
VPN protocol to use. Use CTVPNProtocolIKEv2 for most cases.

`+ (nonnull CTConfig *)create:(nonnull CTConfigBlock)configBlock;`
Factory method to create config.

### CTUserProfile

Describes VPN user.
`@property(strong, nonatomic) NSString *locale;`
User's locale that was used during registration.

`@property(strong, nonatomic) NSString *name;`
User name. Generated for anonymous users.

`@property(strong, nonatomic) NSDictionary *socialProfiles;`
List of social profiles associated with the user. Non-empty only if a social sign-in was used.

`@property(strong, nonatomic, readonly) NSString *email;`
Email, if available by the social provider.

`@property(strong, nonatomic) NSString *registrationTime;`
Time user signed in for the first time.

`@property(strong, nonatomic) NSNumber *activatedDevices;`
A number of devices the user is using (signed in from).

`@property(strong, nonatomic) NSNumber *activeSessions;`
A number of active session user has (signed in right now).

`@property(strong, nonatomic) NSString *authMethod;`
Auth method that was used during sign in.


### CTCountry

Describes VPN server location information

`@property (strong, nonatomic) NSString *countryCode;`  
VPN server country location code. Example: "us", "ru", "ca".

### CTCounters

`@property(strong, nonatomic) NSNumber *tx;`
Bytes transmitted in current session

`@property(strong, nonatomic) NSNumber *rx;`
Bytes received in current session

### CTRemainingTraffic

`@property(nullable, strong, nonatomic) NSNumber *trafficStart;`
UNIX timestamp when the current session was started.

`@property(nullable, strong, nonatomic) NSNumber *trafficLimit;`
Amount of bytes available to current User

`@property(nullable, strong, nonatomic) NSNumber *trafficUsed;`
Amount of bytes User utilized.

`@property(nullable, strong, nonatomic) NSNumber *trafficRemaining;`
Amount of bytes that is available to User.

# Error codes

`CTCakeTubeApiErrorCodeUnknown`
General error code. Please report such errors to Anchorfree Inc. team.

`CTCakeTubeApiErrorCodeSerializationError`
Object serialization error.

`CTCakeTubeApiErrorCodeApiError`
CakeTube backend API error.

`CTCakeTubeApiErrorCodeNilToken`
Attempting to do an action that requires user to be signed in

`CTCakeTubeApiErrorCodeNilUser`
Current user doesn't exist

`CTCakeTubeApiErrorCodeParameters`
Required API parameters are missing.

`CTCakeTubeVPNErrorCodeUndefined`
Unknown VPN error. Please report such errors to Anchorfree Inc. team.

`CTCakeTubeVPNErrorCodeTimeout`
Timeout during VPN connection.

`CTCakeTubeVPNErrorCodeAlreadyConnected`
Attempting to start already connected VPN.

`CTCakeTubeVPNErrorCodeAlreadyDisconnected`
Attempting to stop already disconnected VPN.
