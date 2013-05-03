//
//  TDHTTPClient.m
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 5/3/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import "TDHTTPClient.h"
#import "AFHTTPClient.h"

@interface TDHTTPClient() {
    AFHTTPClient *_client;
}
@end

@implementation TDHTTPClient

-(void) init
{
    _client = [[AFHTTPClient alloc] init];
}
@end
