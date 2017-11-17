//
//  CTOnDemandRules.h
//  caketubesdk
//
//  Created by Yevhen Dubinin on 10/27/17.
//  Copyright © 2017 Anchorfree Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
@interface CTOnDemandRules : NSObject
/*!
 * @property alwaysOnWiFi
 * @description Enable VPN automatically when WiFi is on. Default value is `true`.
 */
@property(nonatomic) BOOL alwaysOnWiFi;
/*!
 * @property alwaysOnCellular
 * @description Enable VPN automatically when cellular data is on (WiFi is off). Default value is `true`.
 */
#if TARGET_OS_IPHONE
@property(nonatomic) BOOL alwaysOnCellular;
#endif
/*!
 * @property probeUrl
 * @description The URL to check before starting VPN. If URL responds with code 200, VPN is started. If valus is `nil`, probing is disabled. Default value is `nil`.
 */
@property(nullable, strong, nonatomic) NSURL *probeUrl;

+ (instancetype)defaultRules;
+ (instancetype)defaultRulesWithProbeURLString:(NSString *)probeURLString;

@end

NS_ASSUME_NONNULL_END
