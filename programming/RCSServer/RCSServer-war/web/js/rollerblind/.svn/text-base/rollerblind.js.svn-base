function rollerblind_moveToPosition(sliderTextId, imgInsideId) {
	var imgInside = document.getElementById(imgInsideId);
        var sliderText = document.getElementById(sliderTextId);
        
        var positionInPromille = parseFloat(1000 - sliderText.value);

	var max = parseFloat(parseInt(imgInside.height) * 19 / 20 * (-1));
	
	if (positionInPromille <= 1000 && positionInPromille >= 0) {
		imgInside.style.top = max * (1 - (positionInPromille / 1000)) + 'px';
        }
}