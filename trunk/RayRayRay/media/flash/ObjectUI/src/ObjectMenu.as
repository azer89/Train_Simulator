package  
{
	import flash.display.MovieClip;
	import flash.display.Stage;
	/**
	 * ...
	 * @author Azer
	 */
	public class ObjectMenu extends MovieClip
	{
		private var _stage:Stage;
		
		public function ObjectMenu(_stage:Stage) 
		{
			this._stage = _stage;
		}
		
		public function setSlider():void
		{
			var track:TrackMc = new TrackMc();
			track.x = 20;
			track.y = 10;
			this.addChild(track);
			
			var slider:SliderMc = new SliderMc();
			slider.x = 20;
			slider.y = 10;
			this.addChild(slider);
			
			var sui:SliderUI = new SliderUI(this._stage, "x", track, slider, 0, 100, 50);
		}
		
	}

}