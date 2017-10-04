//
//  CTAuthMethod.h
//  CakeTubeSDK
//
//  Created by Igor Glotov on 10/2/17.
//  Copyright © 2017 Anchorfree Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString *CTAuthMethodAnonymous;
extern NSString *CTAuthMethodFirebase;
extern NSString *CTAuthMethodCustom;
extern NSString *CTAuthMethodGoogle;
extern NSString *CTAuthMethodFacebook;
extern NSString *CTAuthMethodTwitter;
extern NSString *CTAuthMethodGithub;

@interface CTAuthMethod : NSObject

@property (nonatomic) NSString *method;
@property (nonatomic) NSString *accessToken;

+ (instancetype)anonymous;

+ (instancetype)OAuth:(NSString *)accessToken;

+ (instancetype)facebook:(NSString *)accessToken;

+ (instancetype)google:(NSString *)accessToken;

+ (instancetype)twitter:(NSString *)accessToken;

+ (instancetype)github:(NSString *)accessToken;

+ (instancetype)firebase:(NSString *)accessToken;

+ (instancetype)custom:(NSString *)methodName token:(NSString *)accessToken;

@end
