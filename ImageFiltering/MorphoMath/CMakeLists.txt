SET( MorphoMathName MorphoMath )

ADD_EXECUTABLE( ${MorphoMathName}2D ${MorphoMathName}2D.cxx )
TARGET_LINK_LIBRARIES( ${MorphoMathName}2D ITKIO ITKCommon )

#ADD_EXECUTABLE( ${MorphoMathName}3D ${MorphoMathName}3D.cxx )
#TARGET_LINK_LIBRARIES( ${MorphoMathName}3D ITKIO ITKCommon )

