package  
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	/**
	 * ...
	 * @author Azer
	 */
	public class RayRayRayMenu  extends MovieClip
	{
		private var startButton:StartButton;
		private var stopButton:StopButton;
		private var exitButton:ExitButton;
		
		public function RayRayRayMenu()
		{
			this.setButton();
		}
		
		private function setButton():void
		{
			startButton = new StartButton();
			startButton.x = 90;
			startButton.y = 30;
			startButton.addEventListener(MouseEvent.CLICK, onStartClick, false, 0, true);
			this.addChild(startButton);
			
			stopButton = new StopButton();
			stopButton.x = 90;
			stopButton.y = 30;
			stopButton.addEventListener(MouseEvent.CLICK, onStopClick, false, 0, true);
			this.addChild(stopButton);
			
			exitButton = new ExitButton();
			exitButton.x = 90;
			exitButton.y = 70;
			exitButton.addEventListener(MouseEvent.CLICK, onExitClick, false, 0, true);
			this.addChild(exitButton);
			
			this.startButton.enabled = true;
			this.startButton.visible = true;
			
			this.stopButton.enabled = false;
			this.stopButton.visible = false;
		}
		
		private function onStartClick( event:MouseEvent ):void
		{
			this.startButton.enabled = false;
			this.startButton.visible = false;
			
			this.stopButton.enabled = true;
			this.stopButton.visible = true;
		}
		
		private function onStopClick( event:MouseEvent ):void
		{
			this.startButton.enabled = true;
			this.startButton.visible = true;
			
			this.stopButton.enabled = false;
			this.stopButton.visible = false;
		}
		
		private function onExitClick( event:MouseEvent ):void
		{
		}
		
	}

}