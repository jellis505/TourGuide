var fs = require('fs');

var Classifier = function (imagePath) {
  this.imagePath = imagePath;
};

/*	
 * POST jpg to be classified
 * request: image -> binary rep of image
 * response: ranking[] -> list of {building:index, confidence:percent} items
 *           classifyID -> ID for this request 
 */
Classifier.prototype.classify = function (req, res) {
  if (!req.files.image || req.files.image.type != 'image/jpg')
    return res.send(400);

  var image = req.files.image;
  console.log('image saved at ' + image.path);

  // TODO:
  // Run the classifier.
  var building = { building: 1, confidence: .4 };
  var ranking = {
    ranking: [building],
    classifyID: image.path
  };

  // Send back the result.
  res.send(ranking);
};

/* POST the building the user thinks is correct for an image
 * request: classifyID -> ID for this request
 *          buildingID -> ID for the building
 * response: 200 or 500 if id doesn't exist
 */
Classifier.prototype.confirm = function (req, res) {
  console.log(req.buildingID + ' classified as ' + req.classifyID);
  var path = '/tmp/' + req.buildingID + '/' + req.classifyID;
  var newPath = imagePath + req.classifyID;
  fs.rename(path, newPath, function (err) {
    if (err) throw err;
    res.send('Thank you, human.');
  });
};

module.exports = Classifier;

