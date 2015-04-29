$("#pause-button").on( "click",function  (e) {
	if (e.target.innerHTML=="Continue")
		e.target.innerHTML="Pause";
	else
		e.target.innerHTML="Continue";
});