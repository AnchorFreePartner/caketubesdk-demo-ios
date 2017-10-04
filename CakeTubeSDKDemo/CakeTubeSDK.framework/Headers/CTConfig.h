//
//  CTConfig.h
//  CakeTubeSDK
//
//  Created by Igor Glotov on 10/2/17.
//  Copyright © 2017 Anchorfree Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CTConfig : NSObject
@property (nonnull, strong, nonatomic) NSString *baseUrl;
@property (nonnull, strong, nonatomic) NSString *carrierId;
@property (nonatomic) BOOL debugLogging;

- (nonnull instancetype)initWithBaseUrl:(nonnull NSString *)baseUrl carrierId:(nonnull NSString *)carrierId;
- (nonnull instancetype)initWithBaseUrl:(nonnull NSString *)baseUrl carrierId:(nonnull NSString *)carrierId debugLogging:(BOOL)debugLogging;
@end
