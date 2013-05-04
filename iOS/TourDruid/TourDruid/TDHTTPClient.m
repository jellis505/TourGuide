//
//  TDHTTPClient.m
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 5/3/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import "TDHTTPClient.h"
#import "AFHTTPClient.h"
#import "AFJSONRequestOperation.h"
#import "TDBuildingRanking.h"
#import "TDResponse.h"

@interface TDHTTPClient() {
    AFHTTPClient *_client;
    NSString *_baseURL;
    NSString *_classifyPath;
    NSString *_confirmPath;
}
@end

@implementation TDHTTPClient

-(id) init
{
    self = [super init];
    if (self) {
        _client = [[AFHTTPClient alloc] init];
        //_baseURL = @"http://198.199.67.100:3000";
        _baseURL = @"http://localhost:3000";
        _classifyPath = @"/image/classify";
        _confirmPath = @"/image/confirm";
    }

    return self;
}

+ (TDHTTPClient *)sharedInstance
{
    static dispatch_once_t _singletonPredicate;
    static TDHTTPClient *_singleton = nil;

    dispatch_once(&_singletonPredicate, ^{
        _singleton = [[super allocWithZone:nil] init];
    });

    return _singleton;
}
-(void)confirmImage:(NSNumber *)buildingID classifyID:(NSString *)classifyID
{
    NSArray *objects = [[NSArray alloc] initWithObjects:buildingID, classifyID, nil];
    NSArray *keys = [[NSArray alloc] initWithObjects:@"buildingID",@"classifyID", nil];
    NSDictionary *parameters = [[NSDictionary alloc] initWithObjects:objects forKeys:keys];
    NSURLRequest *request = [_client multipartFormRequestWithMethod:@"POST" path:[self confirmPath] parameters:parameters constructingBodyWithBlock:nil];
    AFJSONRequestOperation *operation = [AFJSONRequestOperation JSONRequestOperationWithRequest:request success:^(NSURLRequest *request, NSHTTPURLResponse *response, id JSON) {
        NSLog(@"Response from server: %@", JSON);
    } failure:^(NSURLRequest *request , NSHTTPURLResponse *response , NSError *error , id JSON ) {
        NSLog(@"Error! %@", error);
    }];
    [operation start];

}

-(NSString *)classifyPath
{
    return [NSString stringWithFormat:@"%@%@", _baseURL, _classifyPath];
}

-(NSString *)confirmPath
{
    return [NSString stringWithFormat:@"%@%@", _baseURL, _confirmPath];
}

-(void)sendImage:(UIImage *)image success:(void(^)(TDResponse *))success
                                  failure:(void (^)(NSError *))failure
{
    NSData *imageData = UIImageJPEGRepresentation(image, 0.5);
    NSURLRequest *request = [_client multipartFormRequestWithMethod:@"POST" path:[self classifyPath] parameters:nil constructingBodyWithBlock: ^(id <AFMultipartFormData> formData) {
        [formData appendPartWithFileData:imageData name:@"image" fileName:@"avatar.png" mimeType:@"image/jpg"];
    }];

    AFJSONRequestOperation *operation = [AFJSONRequestOperation JSONRequestOperationWithRequest:request success:^(NSURLRequest *request, NSHTTPURLResponse *response, id JSON) {
        NSLog(@"Response from server: %@", JSON);
        TDResponse *tdresponse = [[TDResponse alloc] init];
        NSDictionary *jsonDictionary = JSON;
        NSArray *rankings = (NSArray *)[jsonDictionary objectForKey:@"ranking"];
        NSMutableArray *tmp = [[NSMutableArray alloc] init];
        for(NSDictionary *item in rankings) {
            TDBuildingRanking *tdBuildingRanking = [[TDBuildingRanking alloc] init:(NSNumber *)[item objectForKey:@"building"] confidence:(NSNumber *)[item objectForKey:@"confidence"]];
            [tmp addObject:tdBuildingRanking];
        }
        [tdresponse setRanking:tmp];
        [tdresponse setClassifyID:[jsonDictionary objectForKey:@"classifyID"]];
        success(tdresponse);
    } failure:^(NSURLRequest *request , NSHTTPURLResponse *response , NSError *error , id JSON ) {
        failure(error);
    }];
    [operation start];
}
@end
