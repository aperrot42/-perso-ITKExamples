SET( ThresholdingName Thresholding )

ADD_EXECUTABLE( ${ThresholdingName}2D ${ThresholdingName}2D.cxx )
TARGET_LINK_LIBRARIES( ${ThresholdingName}2D ITKIO ITKCommon )

ADD_EXECUTABLE( ${ThresholdingName}3D ${ThresholdingName}3D.cxx )
TARGET_LINK_LIBRARIES( ${ThresholdingName}3D ITKIO ITKCommon )

