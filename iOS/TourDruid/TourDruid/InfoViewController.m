//
//  InfoViewController.m
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 5/10/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import "InfoViewController.h"
#import "TDConstants.h"
#import "MapViewController.h"

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

	// Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)goToMap:(id)sender {
    UIStoryboard *sb = [UIStoryboard storyboardWithName:@"MainStoryboard_iPhone" bundle:nil];
    mapView = [sb instantiateViewControllerWithIdentifier:@"MapView"];
    [mapView setInfoView:self];
    [mapView setImage:[TDConstants mapFromName:_buildingName]];
    [self presentViewController:mapView animated:YES completion:nil];
}
- (void)setBuildingName:(NSString *)buildingName
{
    _buildingName = buildingName;
}
@end
