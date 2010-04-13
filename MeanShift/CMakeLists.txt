SET( MeanShiftName MeanShift )

ADD_EXECUTABLE( ${MeanShiftName} ${MeanShiftName}.cxx )
TARGET_LINK_LIBRARIES( ${MeanShiftName} ITKIO ITKCommon )

