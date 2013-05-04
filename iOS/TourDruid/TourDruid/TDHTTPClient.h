//
//  TDHTTPClient.h
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 5/3/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

@class AFHTTPClient;
@class TDResponse;

@interface TDHTTPClient : NSObject
-(void)sendImage:(UIImage *)image success:(void(^)(TDResponse *))success
         failure:(void (^)(NSError *))failure;
-(void)confirmImage:(NSNumber *)buildingID classifyID:(NSString *)classifyID;

+ (TDHTTPClient *)sharedInstance;
@end
