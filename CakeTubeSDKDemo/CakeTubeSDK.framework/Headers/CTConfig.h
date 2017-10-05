//
//  CTConfig.h
//  CakeTubeSDK
//
//  Created by Igor Glotov on 10/2/17.
//  Copyright © 2017 Anchorfree Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, CTVPNProtocol) {
    CTVPNProtocolIPSec,
    CTVPNProtocolIKEv2
};

@class CTConfig;
typedef void (^CTConfigBlock)(CTConfig *_Nonnull);

@interface CTConfig : NSObject
@property (nonnull, strong, nonatomic) NSString *baseUrl;
@property (nonnull, strong, nonatomic) NSString *carrierId;
@property (nonatomic) CTVPNProtocol vpnProtocol;
@property (nonatomic) BOOL debugLogging;

+ (nonnull CTConfig *)create:(nonnull CTConfigBlock)configBlock;

- (nonnull instancetype)initWithBaseUrl:(nonnull NSString *)baseUrl carrierId:(nonnull NSString *)carrierId;
- (nonnull instancetype)initWithBaseUrl:(nonnull NSString *)baseUrl carrierId:(nonnull NSString *)carrierId debugLogging:(BOOL)debugLogging;
@end
