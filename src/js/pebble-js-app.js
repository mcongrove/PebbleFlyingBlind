Pebble.addEventListener("ready", function(e) {

});

Pebble.addEventListener("showConfiguration", function(e) {
	var options = JSON.parse(window.localStorage.getItem("options"));
	
	var url = "http://wearewearable.com/flying-blind/?v=1.0";
	
	if(options != null) {
		url += "&theme=" + (options["0"] ? encodeURIComponent(options["0"]) : "") +
			"&vibrate=" + (options["1"] && options["1"][0] != null ? encodeURIComponent(options["1"][0]) : "");
	}
	
	Pebble.openURL(url);
});

Pebble.addEventListener("webviewclosed", function(e) {
	if(e.response) {
		var options = JSON.parse(decodeURIComponent(e.response));
		
		window.localStorage.setItem("options", JSON.stringify(options));
		
		Pebble.sendAppMessage(options,
			function(e) {
				console.log("Successfully sent options to Pebble");
			},
			function(e) {
				console.log("Failed to send options to Pebble.\nError: " + e.error.message);
			}
		);
	}
});