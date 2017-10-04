//
//  CTRemainingTraffic.h
//  CakeTubeSDK-iOS
//
//  Created by Sergey Kim on 29.11.16.
//  Copyright © 2016 AnchorFree. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface CTRemainingTraffic : NSObject

@property(nullable, strong, nonatomic) NSString *result;
@property(nullable, strong, nonatomic) NSString *error;

@property(nullable, strong, nonatomic) NSNumber *trafficStart;
@property(nullable, strong, nonatomic) NSNumber *trafficLimit;
@property(nullable, strong, nonatomic) NSNumber *trafficUsed;
@property(nullable, strong, nonatomic) NSNumber *trafficRemaining;

// NOTE: Deprecated
@property(nullable, strong, nonatomic) NSNumber *traffic_start;
@property(nullable, strong, nonatomic) NSNumber *traffic_limit;
@property(nullable, strong, nonatomic) NSNumber *traffic_used;
@property(nullable, strong, nonatomic) NSNumber *traffic_remaining;

- (NSString *)description;

+ (nullable CTRemainingTraffic *)fromDict:(NSDictionary *)dict;

@end
NS_ASSUME_NONNULL_END
