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
    NSString *_url;
}
@end

@implementation TDHTTPClient

-(id) init
{
    self = [super init];
    if (self) {
        _client = [[AFHTTPClient alloc] init];
        _url = @"http://198.199.67.100:3000/image/classify";
        //_url = @"http://localhost:3000/image/classify";
    }

    return self;
}

-(void)sendImage:(UIImage *)image success:(void(^)(TDResponse *))success
                                  failure:(void (^)(NSError *))failure
{
    NSURL *url = [NSURL URLWithString:_url];
    NSLog(@"url %@", url);
    NSData *imageData = UIImageJPEGRepresentation(image, 0.5);
    NSURLRequest *request = [_client multipartFormRequestWithMethod:@"POST" path:_url parameters:nil constructingBodyWithBlock: ^(id <AFMultipartFormData> formData) {
        [formData appendPartWithFileData:imageData name:@"image" fileName:@"avatar.png" mimeType:@"image/png"];
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
        [tdresponse setRequestID:[jsonDictionary objectForKey:@"classifyID"]];
        success(tdresponse);
    } failure:^(NSURLRequest *request , NSHTTPURLResponse *response , NSError *error , id JSON ) {
        failure(error);
    }];
    [operation start];
}
@end
