cmake_minimum_required(VERSION 3.15)

project(firmware_m4 C ASM)

set( CMAKE_COMMON_SRC_DIR  "${CMAKE_SOURCE_DIR}/../src" )
set( CMAKE_COMMON_RSRC_DIR "${CMAKE_SOURCE_DIR}/../ressources" )

message( "Current variables :" )
message( " - CMAKE_SOURCE_DIR      : ${CMAKE_SOURCE_DIR}" )
message( " - CMAKE_COMMON_SRC_DIR  : ${CMAKE_COMMON_SRC_DIR}" )
message( " - CMAKE_COMMON_RSRC_DIR : ${CMAKE_COMMON_RSRC_DIR}" )
message( " - CMAKE_C_FLAGS_INIT    : ${CMAKE_C_FLAGS_INIT}" )
message( " - CMAKE_C_FLAGS         : ${CMAKE_C_FLAGS}" )

# Spécifie la toolchain
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m4)

# Chemin vers la toolchain ARM (adapté si toolchain est dans le PATH)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

# Options du compilateur
set( COMMON_FLAGS
    "-mcpu=cortex-m4 \
    -std=gnu11 \
    -g3 \
    -O0 \
    -ffunction-sections \
    -fdata-sections \
    -Wall \
    -fstack-usage \
    --specs=nano.specs \
    -mfpu=fpv4-sp-d16 \
    -mfloat-abi=hard \
    -mthumb"
)
set( CMAKE_C_FLAGS "${COMMON_FLAGS}")
set( CMAKE_ASM_FLAGS "${COMMON_FLAGS}")
set( CMAKE_EXE_LINKER_FLAGS
    "-mcpu=cortex-m4 \
     -T${CMAKE_COMMON_RSRC_DIR}/STM32MP157AAAX_RAM.ld \
     --specs=nosys.specs \
     -Wl,-Map=${PROJECT_NAME}.map \
     -Wl,--gc-sections \
     -static \
     -mfpu=fpv4-sp-d16 \
     -mfloat-abi=hard \
     -mthumb \
     -Wl,--start-group \
     -lc \
     -lm \
     -Wl,--end-group"
)

# Project source files
file(
    GLOB_RECURSE PROJECT_SRC
    src/*.c
)

# Common source files
file(
    GLOB_RECURSE COMMON_SRC
    ${CMAKE_COMMON_SRC_DIR}/Core/*.c
    ${CMAKE_COMMON_SRC_DIR}/Drivers/STM32MP1xx_HAL_Driver/*.c
    ${CMAKE_COMMON_SRC_DIR}/OpenAMP/libmetal/*.c
    ${CMAKE_COMMON_SRC_DIR}/OpenAMP/open-amp/lib/remoteproc/*.c
    ${CMAKE_COMMON_SRC_DIR}/OpenAMP/open-amp/lib/rpmsg/*.c
    ${CMAKE_COMMON_SRC_DIR}/OpenAMP/open-amp/lib/virtio/*.c
    ${CMAKE_COMMON_SRC_DIR}/OpenAMP/virtual_driver/*.c
    ${CMAKE_COMMON_SRC_DIR}/System/*.c
)

# Project include directories
include_directories(
    src
)

# Common include directories
include_directories(
    ${CMAKE_COMMON_SRC_DIR}/Core
    ${CMAKE_COMMON_SRC_DIR}/Drivers/CMSIS/Device/ST/STM32MP1xx/Include
    ${CMAKE_COMMON_SRC_DIR}/Drivers/CMSIS/Include
    ${CMAKE_COMMON_SRC_DIR}/Drivers/STM32MP1xx_HAL_Driver
    ${CMAKE_COMMON_SRC_DIR}/Drivers/STM32MP1xx_HAL_Driver/Legacy
    ${CMAKE_COMMON_SRC_DIR}/OpenAMP/libmetal/lib/include
    ${CMAKE_COMMON_SRC_DIR}/OpenAMP/open-amp/lib/include
    ${CMAKE_COMMON_SRC_DIR}/OpenAMP/virtual_driver
)

set(STARTUP ${CMAKE_COMMON_RSRC_DIR}/Core/startup_stm32mp157aaax.s)

add_executable(${PROJECT_NAME}.elf ${COMMON_SRC} ${PROJECT_SRC} ${STARTUP})

# Defines
target_compile_definitions(${PROJECT_NAME}.elf PRIVATE
    CORE_CM4
    DEBUG
    METAL_INTERNAL
    METAL_MAX_DEVICE_REGIONS=2
    NO_ATOMIC_64_SUPPORT
    STM32MP157Axx
    USE_HAL_DRIVER
)
