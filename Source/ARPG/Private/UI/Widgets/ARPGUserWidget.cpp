// GluckSeligkeit


#include "UI/Widgets/ARPGUserWidget.h"

void UARPGUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
