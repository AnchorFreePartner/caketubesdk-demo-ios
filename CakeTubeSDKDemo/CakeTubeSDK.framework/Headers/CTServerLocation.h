//
// Created by Igor Glotov on 11/03/15.
// Copyright (c) 2015 AnchorFree. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CTServerLocation : NSObject <NSCoding>

@property(strong, nonatomic) NSString *country;
/**
 Deprecated. This value is no longer available. Always `nil`
 */
@property(strong, nonatomic) NSNumber *servers;

+ (CTServerLocation *)fromDict:(NSDictionary *)dict;

+ (CTServerLocation *)optimal;

- (instancetype)initWithCoder:(NSCoder *)coder;

- (void)encodeWithCoder:(NSCoder *)coder;

@end
