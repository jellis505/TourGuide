var fs = require('fs')
  , path = require('path')
  , exec = require('child_process').exec;

var Classifier = function (imagePath) {
  this.imagePath = imagePath;
};

/*	
 * POST jpg to be classified
 * request: image -> binary rep of image
 * response: ranking[] -> list of building IDs (the building's name)
 *           classifyID -> ID for this request
 */
Classifier.prototype.classify = function (req, res) {
  if (!req.files.image || req.files.image.type != 'image/jpg')
    return res.send(400);

  var image = req.files.image;

  // TODO:
  // Run the classifier.
  var ranking = [];
  var cmd = 'cd ../trainer/build/ && ./predictor ' + image.path;

  var beforeExec = new Date().getTime();
  exec(cmd, function (err, stdout, stderr) {
    if (err) throw err;
    var afterExec = new Date().getTime();
    var total = afterExec - beforeExec;
    console.log('Feature extraction and classification time: ' + total + 'ms');
    stdout.split('\n').map(function (line) {
      var building = line.split('\t')[0];
      ranking.push(building);
    });
    ranking.pop(); // Remove the final newline.
    var uniqueRanking = ranking.filter(function (elem, pos) {
      return ranking.indexOf(elem) == pos;
    });
  	res.send({
        ranking: uniqueRanking,
        classifyID: image.path
  	});
  });
};

/* POST the building the user thinks is correct for an image
 * request: classifyID -> ID for this request
 *          buildingID -> ID for the building
 * response: 200 or 500 if id doesn't exist
 */
Classifier.prototype.confirm = function (req, res) {
  console.log(req.body.classifyID + ' classified as ' + req.body.buildingID);
  var oldPath = req.body.classifyID;
  var splitted = req.body.classifyID.split('/');
  var fileName = splitted[splitted.length - 1];
  var newPath = path.join(this.imagePath, fileName);
  console.log('renaming ' + oldPath + ' to ' + newPath);
  fs.rename(oldPath, newPath, function (err) {
    if (err) throw err;
    res.send('Thank you, human.');
  });
};

module.exports = Classifier;

