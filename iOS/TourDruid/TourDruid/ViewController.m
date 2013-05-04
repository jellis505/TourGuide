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
#import "AnswerViewController.h"
#import "TDResponse.h"

@interface ViewController () {
    @private
    TDHTTPClient *_client;
    ImagePickerViewController *_imagePickerController;
    AnswerViewController *_answerViewController;
}
@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    _client = [TDHTTPClient sharedInstance];
    _imagePickerController = [[ImagePickerViewController alloc] init];
    _answerViewController = [[AnswerViewController alloc] init];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(IBAction)takePhoto :(id)sender

{
    if ([UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera])
    {
        [_imagePickerController setSourceType:UIImagePickerControllerSourceTypeCamera];
    } else {
        [_imagePickerController setSourceType:UIImagePickerControllerSourceTypePhotoLibrary];
    }

    // 
    // Place image picker on the screen
    [_imagePickerController startCameraControllerFromViewController:self usingDelegate:self];
}

//delegate methode will be called after picking photo either from camera or library
- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    NSLog(@"got the picture");
    [self dismissViewControllerAnimated:YES completion:^(){
        NSLog(@"in here");
        UIImage *image = [info objectForKey:UIImagePickerControllerOriginalImage];

        [_client sendImage:image
               success:^(TDResponse *response) {
                   NSLog(@"success!");
                   [_answerViewController loadResponseViewFromController:self
                                                                 response:response];
               }
               failure:^(NSError *error) {
                   NSLog(@"error! %@", error);
               }
         ];
    }];
}
@end
