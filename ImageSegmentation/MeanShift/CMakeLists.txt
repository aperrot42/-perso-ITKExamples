SET( MeanShiftName MeanShift )

ADD_EXECUTABLE( ${MeanShiftName}2D ${MeanShiftName}2D.cxx )
TARGET_LINK_LIBRARIES( ${MeanShiftName}2D ITKIO ITKCommon )

ADD_EXECUTABLE( ${MeanShiftName}3D ${MeanShiftName}3D.cxx )
TARGET_LINK_LIBRARIES( ${MeanShiftName}3D ITKIO ITKCommon )

