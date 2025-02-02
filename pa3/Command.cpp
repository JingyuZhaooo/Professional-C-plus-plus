#include "Command.h"
#include "Shape.h"
#include "PaintModel.h"
#include "DrawCommand.h"
#include "RectShape.h"
#include "EllipseShape.h"
#include "LineShape.h"
#include "PencilShape.h"
#include "SetPenCommand.h"
#include "SetBrushCommand.h"
#include "DeleteCommand.h"
#include "MoveCommand.h"

Command::Command(const wxPoint& start, std::shared_ptr<Shape> shape)
	:mStartPoint(start)
	,mEndPoint(start)
	,mShape(shape)
{

}

// Called when the command is still updating (such as in the process of drawing)
void Command::Update(const wxPoint& newPoint)
{
	mEndPoint = newPoint;
}

std::shared_ptr<Command> CommandFactory::Create(std::shared_ptr<PaintModel> model,
	CommandType type, const wxPoint& start)
{
	std::shared_ptr<Command> retVal;
	// TODO: Actually create a command based on the type passed in
	wxPen currPen = model->GetPen();
	wxBrush currBrush = model->GetBrush();
	switch (type)
	{
		case CM_DrawRect:
		{
			auto rect = std::make_shared<RectShape>(start);
			rect->SetPen(currPen);
			rect->SetBrush(currBrush);
			auto command = std::make_shared<DrawCommand>(start, rect);
			retVal = command;
			break;
		}
		case CM_DrawEllipse:
		{
			auto ellipse = std::make_shared<EllipseShape>(start);
			ellipse->SetPen(currPen);
			ellipse->SetBrush(currBrush);
			auto command = std::make_shared<DrawCommand>(start, ellipse);
			retVal = command;
			break;
		}
		case CM_DrawLine:
		{
			auto line = std::make_shared<LineShape>(start);
			line->SetPen(currPen);
			line->SetBrush(currBrush);
			auto command = std::make_shared<DrawCommand>(start, line);
			retVal = command;
			break;
		}
		case CM_DrawPencil:
		{
			auto pencil = std::make_shared<PencilShape>(start);
			pencil->SetPen(currPen);
			pencil->SetBrush(currBrush);
			auto command = std::make_shared<DrawCommand>(start, pencil);
			retVal = command;
			break;
		}
		case CM_SetPen:
		{
			if (model->GetSelected() != nullptr)	// if a shape is selected
			{
				auto command = std::make_shared<SetPenCommand>(start, model->GetSelected());
				command->Finalize(model);
				retVal = command;
				break;
			}
		}
		case CM_SetBrush:
			if (model->GetSelected() != nullptr)	// if a shape is selected
			{
				auto command = std::make_shared<SetBrushCommand>(start, model->GetSelected());
				command->Finalize(model);
				retVal = command;
				break;
			}
		case CM_Delete:
			if (model->GetSelected() != nullptr)	// if a shape is selected
			{
				auto command = std::make_shared<DeleteCommand>(start, model->GetSelected());
				command->Finalize(model);
				retVal = command;
				break;
			}
		case CM_Move:
			if (model->GetSelected() != nullptr)	// if a shape is selected
			{
				auto command = std::make_shared<MoveCommand>(start, model->GetSelected());
				//command->Finalize(model);
				retVal = command;
				break;
			}
			
	}
	
	return retVal;
}
