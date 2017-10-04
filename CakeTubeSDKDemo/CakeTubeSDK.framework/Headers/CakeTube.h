//
//  CakeTube.h
//  caketubesdk
//
//  Created by Igor Glotov on 9/22/17.
//  Copyright © 2017 Anchorfree Inc. All rights reserved.
//

#ifndef CakeTube_h
#define CakeTube_h

#import <Foundation/Foundation.h>
#import "CTUserProfile.h"
#import "CTServerLocation.h"
#import "CTCounters.h"
#import "CTCredentials.h"
#import "CTRemainingTraffic.h"
#import "CTAuthMethod.h"
#import "CTConfig.h"

typedef void (^CTDefaultCompletion)(NSError *_Nullable error);
typedef void (^CTLoginCompletion)(CTUserProfile *_Nullable subscriber, NSError *_Nullable error);
typedef void (^CTSubscriberCompletion)(CTUserProfile *_Nullable subscriber, NSError *_Nullable error);
typedef void (^CTServersCompletion)(NSArray<CTServerLocation *> *_Nullable servers, NSError *_Nullable error);
typedef void (^CTCountersCompletion)(CTCounters *_Nullable countersResponse, NSError *_Nullable error);
typedef void (^CTVpnStatusCompletion)(BOOL isVpn, NSError *_Nullable error);
typedef void (^CTRemainingTrafficCompletion)(CTRemainingTraffic *_Nullable remainingTraffic, NSError *_Nullable error);
typedef void (^CTPurchaseCompletion)(NSString *_Nullable status, NSError *_Nullable error);
typedef void (^CTStartVPNCompletion)(CTServerLocation *_Nullable server, NSError *_Nullable error);

NS_ASSUME_NONNULL_BEGIN

extern NSString *const kCTCakeTubeApiErrorDomain;

typedef NS_ENUM(NSInteger, CTCakeTubeApiErrorCode) {
    /*! @const CTCakeTubeApiErrorCodeUnknown This is a generic unknown error, please report such errors to developers */
    CTCakeTubeApiErrorCodeUnknown = 301,
    /*! @const CTCakeTubeApiErrorCodeSerializationError API serialization/deserialization error */
    CTCakeTubeApiErrorCodeSerializationError = 302,
    CTCakeTubeApiErrorCodeApiError = 303,
    CTCakeTubeApiErrorCodeNilToken = 600,
    CTCakeTubeApiErrorCodeNilUser = 601,
    CTCakeTubeApiErrorCodeParameters = 602,
    CTCakeTubeApiErrorCodeVpnNotVerified = 603
};

extern NSString *const kCTCakeTubeVPNErrorDomain;

typedef NS_ENUM(NSInteger, CTCakeTubeVPNErrorCode) {
    CTCakeTubeVPNErrorCodeUndefined = 500,
    CTCakeTubeVPNErrorCodeTimeout = 501,
    CTCakeTubeVPNErrorCodeAlreadyConnected = 502,
    CTCakeTubeVPNErrorCodeAlreadyDisconnected = 503,
    CTCakeTubeVPNErrorCodeConnectInvalid = 504,
    CTCakeTubeVPNErrorCodeDisconnectInvalid = 505
};

/**
 Observe NSNotificationCenter.defaultCenter for this notification to obtain VPN status changes. Updated status
 is available through `vpnStatus` property.
 */
extern NSString *const CTVPNStatusDidChangeNotification;

typedef NS_ENUM(NSInteger, CTVPNStatus) {
    CTVPNStatusUndefined = 0,
    CTVPNStatusInvalid = 1,
    CTVPNStatusDisconnected = 2,
    CTVPNStatusConnecting = 3,
    CTVPNStatusConnected = 4,
    CTVPNStatusDisconnecting = 5,
};

@interface CakeTube : NSObject

@property (readonly) CTVPNStatus vpnStatus;

+ (CakeTube *)instance;

- (void)configure:(CTConfig *)config;

- (BOOL)isLoggedIn;

- (void)loginWithMethod:(CTAuthMethod *)method completion:(nullable CTLoginCompletion)completion;

- (void)startVPN:(nullable CTStartVPNCompletion)completion;

- (void)stopVPN:(nullable CTDefaultCompletion)completion;

- (void)removeVPNProfile:(nullable CTDefaultCompletion)completion;

- (void)subscriberInfo:(nullable CTSubscriberCompletion)completion;

- (void)availableServers:(nullable CTServersCompletion)completion;

- (void)trafficStats:(nullable CTCountersCompletion)completion;

- (void)checkVpnIsEnabled:(nullable CTVpnStatusCompletion)completion;

- (void)remainingTraffic:(nullable CTRemainingTrafficCompletion)completion;

- (void)logout:(nullable CTDefaultCompletion)completion;

/**
 Checks if the product was purchased and purchase is valid and active
 @param receipt     - base64 encoded string of receipt data
 @param completion completion Completion
 */
- (void)checkPurchaseWithReceipt:(NSString *)receipt
                      completion:(nullable CTPurchaseCompletion)completion;

/**
 Sets server location. If VPN is already connected, this method does not reconnect VPN to a new server.
 @param location - Server location, obtained with [CakeTube getServers:] or [CTServerLocation optimal].
 nil value means the location will be optimal.
 */
- (void)setServer:(nullable CTServerLocation *)location;

- (nullable CTServerLocation *)getServer;

- (nullable NSString *)accessToken;

@end

NS_ASSUME_NONNULL_END
#endif
