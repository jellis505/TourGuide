//
//  AnswerViewController.m
//  TourDruid
//
//  Created by Cody Geronimo De La Vara on 5/3/13.
//  Copyright (c) 2013 Kin. All rights reserved.
//

#import "AnswerViewController.h"
#import "TDBuildingRanking.h"
#import "TDResponse.h"
#import "TDHTTPClient.h"

@interface AnswerViewController () {
    @private
    NSArray *_ranking;
    TDResponse *_response;
    TDHTTPClient *_client;
}

@end

@implementation AnswerViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    UIStoryboard *sb = [UIStoryboard storyboardWithName:@"MainStoryboard_iPhone" bundle:nil];
    self = [sb instantiateViewControllerWithIdentifier:@"ResultView"];
    if (self) {
        // Custom initialization
    }

    _client = [TDHTTPClient sharedInstance];
    return self;
}

- (void)viewDidLoad
{
    if (_client == nil) {
        _client = [TDHTTPClient sharedInstance];
    }
    [super viewDidLoad];
	// Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView*)tableView numberOfRowsInSection:(NSInteger)section {
    return [_ranking count];
}

-(void) setRanking:(NSArray *)ranking {
    _ranking = ranking;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString *cellId = @"C1";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellId];

    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:cellId];
    }

    TDBuildingRanking *rank = [_ranking objectAtIndex:indexPath.row];
    cell.textLabel.text = [rank name];
    double percentage = 100 * [[rank confidence] doubleValue];

    cell.detailTextLabel.text = [NSString stringWithFormat:@"%@%%",[[NSNumber numberWithDouble:percentage] stringValue]];
     return cell;
}

- (BOOL)loadResponseViewFromController:(UIViewController*) controller
                              response:(TDResponse *)response
{
    _ranking = response.ranking;
    _response = response;
    [controller presentViewController:self animated:YES completion:nil];
    return YES;
}

#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
//    TDBuildingRanking *rank = (TDBuildingRanking *)[_ranking objectAtIndex:indexPath.row];
//    NSString *alertMessage = [NSString stringWithFormat:@"You sure it's %@?", rank.name];
//    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Confirm selection"
//                                                    message:alertMessage
//                                                   delegate:self
//                                          cancelButtonTitle:@"Nope :("
//                                          otherButtonTitles:@"Yup!", nil];
//    [alert show];
    TDBuildingRanking *rank = [_ranking objectAtIndex:indexPath.row];
    NSLog(@"%@", [rank buildingId]);
    [_client confirmImage:[rank buildingId] classifyID:[_response classifyID]];
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    NSLog(@"selected");
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex) {
        
    }
}
@end
