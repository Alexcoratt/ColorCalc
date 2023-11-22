#ifndef PAINT_CALCULATION_OPTION_METHODS
#define PAINT_CALCULATION_OPTION_METHODS

#include "PaintDataManager.hpp"
#include "LacquerDataManager.hpp"
#include "FoilDataManager.hpp"
#include "FoilRollsDataManager.hpp"

namespace common_option_methods {

	void clearValues(IDataManager *);
	void calculateResourceAmount(IDataManager const *);
	void writeParameters(IDataManager const *);

	void loadPreset(IDataManager *);
	void createPreset(IDataManager *);
	void updatePreset(IDataManager *);
	void removePreset(IDataManager *);

}

namespace paint_calculation_option_methods {

	void setPaintType(PaintDataManager *);
	void setMaterialType(PaintDataManager *);
	void setConsumption(PaintDataManager *);
	void setDivider(PaintDataManager *);
	void setPercentage(PaintDataManager *);
	void setSheetWidth(PaintDataManager *);
	void setSheetLength(PaintDataManager *);
	void setCirculation(PaintDataManager *);
	void setReserve(PaintDataManager *);

}

namespace lacquer_calculation_option_methods {

	void setPercentage(LacquerDataManager *);
	void setConsumption(LacquerDataManager *);
	void setSheetLength(LacquerDataManager *);
	void setSheetWidth(LacquerDataManager *);
	void setCircualtion(LacquerDataManager *);

}

namespace foil_calculation_option_methods {

	void setCirulation(FoilDataManager *);
	void setLength(FoilDataManager *);
	void setWidth(FoilDataManager *);
	void setSheetNumber(FoilDataManager *);
	void setLengthReserve(FoilDataManager *);
	void setWidthReserve(FoilDataManager *);
	void calculateFoilRollLength(FoilDataManager const *);
	void writeSuitableRolls(FoilDataManager const *);

}

namespace foil_rolls_option_methods {

	void setLength(FoilRollsDataManager *);
	void setWidth(FoilRollsDataManager *);

}

#endif
