package  
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.display.DisplayObject;
	/**
	 * ...
	 * @author Azer
	 */
	public class RayRayRayMenu  extends MovieClip
	{
		private var startButton:StartButton;
		private var stopButton:StopButton;
		private var exitButton:ExitButton;
		private var fpsInfo:FPSInfo;
		private var fpsText:TextField;
		
		public function RayRayRayMenu()
		{
			this.setButton();
			
			ExternalInterface.addCallback("setFPS", setFPS);
		}
		
		private function setButton():void
		{
			fpsInfo = new FPSInfo();
			fpsInfo.x = 95;
			fpsInfo.y = 40;
			this.addChild(fpsInfo);
			
			startButton = new StartButton();
			startButton.x = 90;
			startButton.y = 70;
			startButton.addEventListener(MouseEvent.CLICK, onStartClick, false, 0, true);
			this.addChild(startButton);
			
			stopButton = new StopButton();
			stopButton.x = 90;
			stopButton.y = 70;
			stopButton.addEventListener(MouseEvent.CLICK, onStopClick, false, 0, true);
			this.addChild(stopButton);
			
			exitButton = new ExitButton();
			exitButton.x = 90;
			exitButton.y = 110;
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
			
			ExternalInterface.call("Start", "start");
		}
		
		private function onStopClick( event:MouseEvent ):void
		{
			this.startButton.enabled = true;
			this.startButton.visible = true;
			
			this.stopButton.enabled = false;
			this.stopButton.visible = false;
			
			//ExternalInterface.call("Stop", "stop");
		}
		
		private function onExitClick( event:MouseEvent ):void
		{
			//ExternalInterface.call("Exit", "exit");
		}
		
		private function setObjects():void
		{
			var c:DisplayObject = null;
			
			for (var a:int = 0; a < this.fpsInfo.numChildren; a++)
			{
				c = this.fpsInfo.getChildAt(a);
				{
					if (c.name == "fpsText")
					{
						fpsText = (TextField)(c);
						fpsText.text = "fps: XXX";
					}
				}
			}
		}
		
		private function setFPS(fps:Number):void
		{
			fpsText.text = "fps: " + fps.toString();
		}
		
	}

}