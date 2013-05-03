//
//  ViewController.m
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 4/23/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import "ViewController.h"
#import "ImagePickerViewController.h"
#import "TDHTTPClient.h"

@interface ViewController () {
    @private
    TDHTTPClient *_client;
}
@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    _client = [[TDHTTPClient alloc] init];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(IBAction)takePhoto :(id)sender

{
    ImagePickerViewController *imagePickerController = [[ImagePickerViewController alloc] init];

    if ([UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera])
    {
        [imagePickerController setSourceType:UIImagePickerControllerSourceTypeCamera];
    }

    // 
    // Place image picker on the screen
    [imagePickerController startCameraControllerFromViewController:self usingDelegate:self];
}

//delegate methode will be called after picking photo either from camera or library
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    NSLog(@"got the picture");
    [self dismissViewControllerAnimated:YES completion:nil];
    UIImage *image = [info objectForKey:UIImagePickerControllerOriginalImage];
    
}
@end
