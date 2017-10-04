//
// Created by Igor Glotov on 22/02/15.
// Copyright (c) 2015 AnchorFree. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "CTConnectionService.h"

@class CTUserProfile;
@class CTCounters;
@class CTCredentials;
@class CTRemainingTraffic;
@class CTServerLocation;

extern NSString *_Nonnull const kCTCakeTubeApiErrorDomain;

typedef void (^CTLoginBlock)(NSError *_Nullable error, CTUserProfile *_Nullable subscriber);

typedef void (^CTCredentialsBlock)(NSError *_Nullable error, CTCredentials *_Nullable credentials);

typedef void (^CTSubscriberBlock)(NSError *_Nullable error, CTUserProfile *_Nullable subscriber);

typedef void (^CTServersBlock)(NSError *_Nullable error, NSArray<CTServerLocation *> *_Nullable servers);

typedef void (^CTCountersBlock)(NSError *_Nullable error, CTCounters *_Nullable countersResponse);

typedef void (^CTVpnStatusBlock)(NSError *_Nullable error, BOOL isVpn);

typedef void (^CTRemainingTrafficBlock)(NSError *_Nullable error, CTRemainingTraffic *_Nullable remainingTraffic);

typedef void (^CTSuccessBlock)(void);

typedef void (^CTFailureBlock)(NSError *_Nullable error);

typedef void (^CTPurchaseBlock)(NSError *_Nullable error, NSString *_Nullable status);

NS_ASSUME_NONNULL_BEGIN

extern NSString *CTClientServiceSessionDidChangeNotification;

extern NSString *CTClientServiceAuthMethodCustom;
extern NSString *CTClientServiceAuthMethodGoogle;
extern NSString *CTClientServiceAuthMethodFacebook;
extern NSString *CTClientServiceAuthMethodTwitter;
extern NSString *CTClientServiceAuthMethodAnonymous;
extern NSString *CTClientServiceAuthMethodFirebase;

@interface CTClientService : NSObject

+ (CTClientService *)sharedInstance;

@property(strong, readonly) CTUserProfile *subscriber;
@property(atomic, strong) NSNotificationCenter *notificationCenter;

@property(readonly) NSString *carrierId;
@property(readonly) NSString *baseUrl;

NS_ASSUME_NONNULL_END

- (void)setDebugLogging:(BOOL)enable;

- (void)configureWithBaseURL:(nonnull NSString *)baseURL carrierId:(nonnull NSString *)carrierId;

- (BOOL)isLoggedIn;

- (void)loginWithOAuthToken:(nonnull NSString *)accessToken complete:(nullable CTLoginBlock)completion;

- (void)loginWithOAuthToken:(nullable NSString *)accessToken
                 authMethod:(nonnull NSString *)authMethod
                   complete:(nonnull CTLoginBlock)completion;

- (void)getCredentialsWithCompletion:(nullable CTCredentialsBlock)completion;

- (void)checkCurrentCredentialsWithCompletion:(nullable void (^)(NSError * _Nullable error))completion;

- (void)getSubscriberInfo:(nullable CTSubscriberBlock)completion;

- (void)getServers:(nullable CTServersBlock)completion;

- (void)getTrafficStats:(nullable CTCountersBlock)completion;

- (void)checkIsVpn:(nullable CTVpnStatusBlock)completion;

- (void)getRemainingTrafficWithCompletion:(nullable CTRemainingTrafficBlock)completion;

- (void)logoutWithCompletion:(nullable CTFailureBlock)completion;

/**
 Checks if the product was purchased and purchase is valid and active
 @param receipt     - base64 encoded string of receipt data
 @param completion completion block
 */
- (void)checkPurchaseWithReceipt:(nonnull NSString *)receipt
                      completion:(nullable CTPurchaseBlock)completion;

- (void)setServer:(nullable CTServerLocation *)location;

- (nullable CTServerLocation *)getServer;

- (nullable NSString *)accessToken;

// Deprecated APIs

/**
 Deprecated. Use setServer:(CTServerLocation *) instead.
 */
- (void)setCurrentServer:(nullable NSString *)location;

/**
 Deprecated. Use getServer instead.
 */
- (nullable NSString *)getCurrentServer;

/**
 Deprecated. Use configureWithBaseURL:(NSString *) carrierId:(NSString *) instead.
 */
- (void)configureWithBaseURLs:(NSArray *_Nonnull)baseURLs carrierId:(NSString *_Nonnull)carrierId;

@end
