
add_executable(test_car test_car.cpp)
add_test(NAME test_car COMMAND test_car)
target_link_libraries(test_car PRIVATE Catch2::Catch2WithMain carlib)
