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
		
		private var curveOption:CurveOption;
		private var prev:PrevButton;
		private var next:NextButton;
		private var curveText:TextField;
		private var curveVal:int;
		
		public function RayRayRayMenu()
		{
			this.setButton();
			this.setObjects();
			curveVal = 0;
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
			
			curveOption = new CurveOption();
			curveOption.x = 90;
			curveOption.y = 110;
			menu.addChild(curveOption);
			
			exitButton = new ExitButton();
			exitButton.x = 90;
			exitButton.y = 150;
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
		
		private function onNextClick( event:MouseEvent ):void
		{
			curveVal++;
			setCurve();
		}
		
		private function onPrevClick( event:MouseEvent ):void
		{
			curveVal--;
			setCurve();
		}
		
		private function setCurve():void
		{
			curveVal = Math.abs(curveVal);			
			if (curveVal > 1) curveVal = 0;
			
			if (curveVal == 0) 
			{
				curveText.text = "BEZIER";
				ExternalInterface.call("Curve", "bezier");
			}
			else if (curveVal == 1) 
			{
				curveText.text = "B-SPLINE";
				ExternalInterface.call("Curve", "bspline");
			}
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
				
				if (c.name == "FpsText")
				{
					fpsText = (TextField)(c);
					fpsText.text = "FPS: -";
				}
			}
			
			for (var b:int = 0; b < this.curveOption.numChildren; b++ )
			{
				c = this.curveOption.getChildAt(b);
				
				if (c.name == "curveText")
				{
					curveText = (TextField)(c);
					//curveText.text = "B-SPLINE";
				}
				else if (c.name == "next")
				{
					next = (NextButton)(c);
					next.addEventListener(MouseEvent.CLICK, onNextClick, false, 0, true);
				}
				else if (c.name == "prev")
				{
					prev = (PrevButton)(c);
					prev.addEventListener(MouseEvent.CLICK, onPrevClick, false, 0, true);
				}
			}
		}
		
		private function setFPS(fps:Number):void
		{
			fpsText.text = "FPS: " + fps.toString();
		}
		
	}

}