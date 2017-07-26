var angle = 0, image, interval;
		
function initFan(divId, imgSrc) {
    var R = Raphael(divId, 100, 100);
    image = R.image(imgSrc, 0, 0, 100, 100);
}
		
function startFan() {
    clearInterval(interval);
    interval = setInterval(function() {
            image.animate({ transform: "r" + angle }, 1, "");
            angle += 5;
        }, 7);
}
	
function stopFan() {
    clearInterval(interval);
}