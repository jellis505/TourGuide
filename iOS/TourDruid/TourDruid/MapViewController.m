//
//  MapViewController.m
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 5/11/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import "MapViewController.h"
#import "InfoViewController.h"
@interface MapViewController () {
    UIImage *_image;
}

@end

@implementation MapViewController

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
    [_mapImage setImage:_image];
	// Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)infoView:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void) setImage:(UIImage *)image {
    _image = image;
}

@end
