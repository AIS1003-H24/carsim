
add_library(carlib
        "Car.cpp"
)
target_include_directories(carlib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(carlib PUBLIC threepp::threepp)
