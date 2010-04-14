SET( ThresholdingName Thresholding )

ADD_EXECUTABLE( ${ThresholdingName} ${ThresholdingName}.cxx )
TARGET_LINK_LIBRARIES( ${ThresholdingName} ITKIO ITKCommon )

