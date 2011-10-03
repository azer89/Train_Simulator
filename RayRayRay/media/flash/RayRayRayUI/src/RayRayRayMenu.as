package  
{
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	import flash.external.ExternalInterface;
	import flash.text.TextField;
	import flash.text.TextFormat;
	import flash.display.DisplayObject;
	
	import com.greensock.*;
	import com.greensock.easing.*;
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
		private var menu:MovieClip;
		private var gearIcon:GearIcon;
		private var isDown:Boolean = true;
		
		public function RayRayRayMenu()
		{
			this.setButton();
			this.setObjects();
			
			ExternalInterface.addCallback("setFPS", setFPS);
		}
		
		private function setButton():void
		{
			gearIcon = new GearIcon();
			gearIcon.x = 35;
			gearIcon.y = 35;
			gearIcon.addEventListener(MouseEvent.CLICK, onGearClick, false, 0, true);
			this.addChild(gearIcon);
			
			menu = new MovieClip();
			menu.x = 0;
			//menu.y = 50;
			menu.y = -200;
			menu.alpha = 0;
			
			fpsInfo = new FPSInfo();
			fpsInfo.x = 95;
			fpsInfo.y = 40;
			menu.addChild(fpsInfo);
			
			startButton = new StartButton();
			startButton.x = 90;
			startButton.y = 70;
			startButton.addEventListener(MouseEvent.CLICK, onStartClick, false, 0, true);
			menu.addChild(startButton);
			
			stopButton = new StopButton();
			stopButton.x = 90;
			stopButton.y = 70;
			stopButton.addEventListener(MouseEvent.CLICK, onStopClick, false, 0, true);
			menu.addChild(stopButton);
			
			exitButton = new ExitButton();
			exitButton.x = 90;
			exitButton.y = 110;
			exitButton.addEventListener(MouseEvent.CLICK, onExitClick, false, 0, true);
			menu.addChild(exitButton);
			
			this.addChild(menu);
			
			this.startButton.enabled = true;
			this.startButton.visible = true;
			
			this.stopButton.enabled = false;
			this.stopButton.visible = false;
		}
		
		private function onGearClick( event:MouseEvent ):void
		{
			if(isDown)
				TweenMax.to(menu, 0.5, { x:0, y:50, ease:Circ.easeOut, alpha:1 } );
			else
				TweenMax.to(menu, 0.5, { x:0, y:-200, ease:Circ.easeIn, alpha:0 } );
				
			isDown = !isDown;
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
			
			ExternalInterface.call("Stop", "stop");
		}
		
		private function onExitClick( event:MouseEvent ):void
		{
			ExternalInterface.call("Exit", "exit");
		}
		
		private function setObjects():void
		{
			var c:DisplayObject = null;
			
			for (var a:int = 0; a < this.fpsInfo.numChildren; a++)
			{
				c = this.fpsInfo.getChildAt(a);
				{
					if (c.name == "FpsText")
					{
						fpsText = (TextField)(c);
						fpsText.text = "fps: -";
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