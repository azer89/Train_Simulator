package  
{
	import flash.display.MovieClip;
	import flash.display.Stage;
	import flash.external.ExternalInterface;
	/**
	 * ...
	 * @author Azer
	 */
	public class ObjectMenu extends MovieClip
	{
		private var _stage:Stage;
		private var track:TrackMc;
		private var slider:SliderMc;
		private var sui:SliderUI;
		
		public function ObjectMenu(_stage:Stage) 
		{
			this._stage = _stage;
			
			ExternalInterface.addCallback("setVal", setVal);
		}
		
		public function setSlider():void
		{
			var heightText:HeightText = new HeightText();
			heightText.x = 20;
			heightText.y = 0;
			this.addChild(heightText);
			
			track = new TrackMc();
			track.x = 20;
			track.y = 30;
			this.addChild(track);
			
			slider = new SliderMc();
			slider.x = 20;
			slider.y = 30;
			this.addChild(slider);
			
			sui = new SliderUI(this._stage, "x", track, slider, 0, 50, 0);
			//var sui:SliderUI = new SliderUI(this._stage, "x", track, slider, 0, 50, 0);
		}
		
		private function setVal(val:Number):void
		{
			sui.destroy();
			sui = new SliderUI(this._stage, "x", track, slider, 0, 50, val);
			
		}
		
	}

}