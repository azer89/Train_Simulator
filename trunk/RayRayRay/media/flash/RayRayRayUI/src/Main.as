package 
{
	import flash.display.Sprite;
	import flash.events.Event;
	
	/**
	 * ...
	 * @author Reza Adhitya Saputra
	 */
	public class Main extends Sprite 
	{
		
		public function Main():void 
		{
			if (stage) init();
			else addEventListener(Event.ADDED_TO_STAGE, init);
		}
		
		private function init(e:Event = null):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, init);
			// entry point
			
			var menu:RayRayRayMenu = new RayRayRayMenu();
			menu.x = 0;
			menu.y = 0;
			this.addChild(menu);
			
		}
		
	}
	
}