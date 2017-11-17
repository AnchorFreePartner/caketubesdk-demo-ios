//
//  CTConnectionServiceBase.h
//  CakeTubeSDK
//
//  Created by Valentin Shergin on 05/05/15.
//  Copyright (c) 2015 AnchorFree. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CTConstants.h"

extern NSString *CTConnectionServiceStatusDidChangeNotification;
extern NSString *CTConnectionServiceTrafficInformationDidChangeNotification;

typedef NS_ENUM(NSInteger, CTConnectionServiceStatus) {
    CTConnectionServiceStatusUndefined = 0,
    CTConnectionServiceStatusInvalid = 1,
    CTConnectionServiceStatusDisconnected = 2,
    CTConnectionServiceStatusConnecting = 3,
    CTConnectionServiceStatusConnected = 4,
    CTConnectionServiceStatusDisconnecting = 5,
};

@interface CTConnectionServiceBase : NSObject

+ (instancetype)sharedInstance;

@property(atomic, strong) NSNotificationCenter *notificationCenter;
@property(atomic) CTConnectionServiceStatus status;

- (void)connectWithCompletion:(void (^)(NSError *error))completion;

- (void)disconnectWithCompletion:(void (^)(NSError *error))completion;

- (void)removeProfileFromPreferencesWithCompletion:(void (^)(NSError *error))completion;

- (void)installProfileIntoPreferencesWithCompletion:(void (^)(NSError *error))completion;
@end
