w = ui.newScreen()

local btnCallback = function ()
	w.disable()
	ptp.takePicture()
	w.enable()
end

w.addButton("Press Shutter", btnCallback)
