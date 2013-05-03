
/*
 * GET users listing.
 */

/*	
 * POST image to be classified
 * request: image -> binary rep of image
 * response: ranking[] -> list of {building:index, confidence:percent} items
 * 			 classifyId -> id for this request 
 */
exports.classify = function (req, res) {
	
  res.send("");
};

/* POST image the user thinks is correct
 * request: classifyId -> id for this request
 *			buildingId -> id for the building
 * response: 200 or 500 if id doesn't exist
 */
exports.confirm = function (req, res) {
  res.send("respond with a resource");
};
