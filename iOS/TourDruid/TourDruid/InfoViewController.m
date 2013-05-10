//
//  InfoViewController.m
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 5/10/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import "InfoViewController.h"
#import "TDConstants.h"

@interface InfoViewController () {
    @private
    NSString *_buildingName;
    NSURL *_wikiURL;
}

@end

@implementation InfoViewController
@synthesize mapView;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    NSString *fullURL = [TDConstants urlFromName:_buildingName];
    NSLog(@"name %@", _buildingName);
    NSString *readabilityURL = [NSString stringWithFormat:@"%@%@", @"http://www.readability.com/m?url=", fullURL];
    NSURL *url = [NSURL URLWithString:readabilityURL];
    NSURLRequest *requestObj = [NSURLRequest requestWithURL:url];
    [_webView loadRequest:requestObj];
    mapView.region = [TDConstants regionFromName:_buildingName];
	// Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)setBuildingName:(NSString *)buildingName
{
    _buildingName = buildingName;
}
@end
