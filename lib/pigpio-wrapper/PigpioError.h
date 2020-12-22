#ifndef __PIGPIOERROR_H__
#define __PIGPIOERROR_H__

#include "optional.hpp"

enum class PigpioError
{
    PI_UNEXPECTED_ERROR = 1000, // an error occurred that is not valid for called method
    pigif_bad_send = -2000,
    pigif_bad_recv = -2001,
    pigif_bad_getaddrinfo = -2002,
    pigif_bad_connect = -2003,
    pigif_bad_socket = -2004,
    pigif_bad_noib = -2005,
    pigif_duplicate_callback = -2006,
    pigif_bad_malloc = -2007,
    pigif_bad_callback = -2008,
    pigif_notify_failed = -2009,
    pigif_callback_not_found = -2010,
    pigif_unconnected_pi = -2011,
    pigif_too_many_pis = -2012,
    PI_OK = 0,                  // everything is fine
    PI_INIT_FAILED = -1,        // gpioInitialise failed
    PI_BAD_USER_GPIO = -2,      // GPIO not 0-31
    PI_BAD_GPIO = -3,           // GPIO not 0-53
    PI_BAD_MODE = -4,           // mode not 0-7
    PI_BAD_LEVEL = -5,          // level not 0-1
    PI_BAD_PUD = -6,            // pud not 0-2
    PI_BAD_PULSEWIDTH = -7,     // pulsewidth not 0 or 500-2500
    PI_BAD_DUTYCYCLE = -8,      // dutycycle outside set range
    PI_BAD_TIMER = -9,          // timer not 0-9
    PI_BAD_MS = -10,            // ms not 10-60000
    PI_BAD_TIMETYPE = -11,      // timetype not 0-1
    PI_BAD_SECONDS = -12,       // seconds < 0
    PI_BAD_MICROS = -13,        // micros not 0-999999
    PI_TIMER_FAILED = -14,      // gpioSetTimerFunc failed
    PI_BAD_WDOG_TIMEOUT = -15,  // timeout not 0-60000
    PI_NO_ALERT_FUNC = -16,     // DEPRECATED
    PI_BAD_CLK_PERIPH = -17,    // clock peripheral not 0-1
    PI_BAD_CLK_SOURCE = -18,    // DEPRECATED
    PI_BAD_CLK_MICROS = -19,    // clock micros not 1, 2, 4, 5, 8, or 10
    PI_BAD_BUF_MILLIS = -20,    // buf millis not 100-10000
    PI_BAD_DUTYRANGE = -21,     // dutycycle range not 25-40000
    PI_BAD_DUTY_RANGE = -21,    // DEPRECATED (use PI_BAD_DUTYRANGE)
    PI_BAD_SIGNUM = -22,        // signum not 0-63
    PI_BAD_PATHNAME = -23,      // can't open pathname
    PI_NO_HANDLE = -24,         // no handle available
    PI_BAD_HANDLE = -25,        // unknown handle
    PI_BAD_IF_FLAGS = -26,      // ifFlags > 4
    PI_BAD_CHANNEL = -27,       // DMA channel not 0-15
    PI_BAD_PRIM_CHANNEL = -27,  // DMA primary channel not 0-15
    PI_BAD_SOCKET_PORT = -28,   // socket port not 1024-32000
    PI_BAD_FIFO_COMMAND = -29,  // unrecognized fifo command
    PI_BAD_SECO_CHANNEL = -30,  // DMA secondary channel not 0-15
    PI_NOT_INITIALISED = -31,   // function called before gpioInitialise
    PI_INITIALISED = -32,       // function called after gpioInitialise
    PI_BAD_WAVE_MODE = -33,     // waveform mode not 0-3
    PI_BAD_CFG_INTERNAL = -34,  // bad parameter in gpioCfgInternals call
    PI_BAD_WAVE_BAUD = -35,     // baud rate not 50-250K(RX)/50-1M(TX)
    PI_TOO_MANY_PULSES = -36,   // waveform has too many pulses
    PI_TOO_MANY_CHARS = -37,    // waveform has too many chars
    PI_NOT_SERIAL_GPIO = -38,   // no bit bang serial read on GPIO
    PI_BAD_SERIAL_STRUC = -39,  // bad (null) serial structure parameter
    PI_BAD_SERIAL_BUF = -40,    // bad (null) serial buf parameter
    PI_NOT_PERMITTED = -41,     // GPIO operation not permitted
    PI_SOME_PERMITTED = -42,    // one or more GPIO not permitted
    PI_BAD_WVSC_COMMND = -43,   // bad WVSC subcommand
    PI_BAD_WVSM_COMMND = -44,   // bad WVSM subcommand
    PI_BAD_WVSP_COMMND = -45,   // bad WVSP subcommand
    PI_BAD_PULSELEN = -46,      // trigger pulse length not 1-100
    PI_BAD_SCRIPT = -47,        // invalid script
    PI_BAD_SCRIPT_ID = -48,     // unknown script id
    PI_BAD_SER_OFFSET = -49,    // add serial data offset > 30 minutes
    PI_GPIO_IN_USE = -50,       // GPIO already in use
    PI_BAD_SERIAL_COUNT = -51,  // must read at least a byte at a time
    PI_BAD_PARAM_NUM = -52,     // script parameter id not 0-9
    PI_DUP_TAG = -53,           // script has duplicate tag
    PI_TOO_MANY_TAGS = -54,     // script has too many tags
    PI_BAD_SCRIPT_CMD = -55,    // illegal script command
    PI_BAD_VAR_NUM = -56,       // script variable id not 0-149
    PI_NO_SCRIPT_ROOM = -57,    // no more room for scripts
    PI_NO_MEMORY = -58,         // can't allocate temporary memory
    PI_SOCK_READ_FAILED = -59,  // socket read failed
    PI_SOCK_WRIT_FAILED = -60,  // socket write failed
    PI_TOO_MANY_PARAM = -61,    // too many script parameters (> 10)
    PI_NOT_HALTED = -62,        // DEPRECATED
    PI_SCRIPT_NOT_READY = -62,  // script initialising
    PI_BAD_TAG = -63,           // script has unresolved tag
    PI_BAD_MICS_DELAY = -64,    // bad MICS delay (too large)
    PI_BAD_MILS_DELAY = -65,    // bad MILS delay (too large)
    PI_BAD_WAVE_ID = -66,       // non existent wave id
    PI_TOO_MANY_CBS = -67,      // No more CBs for waveform
    PI_TOO_MANY_OOL = -68,      // No more OOL for waveform
    PI_EMPTY_WAVEFORM = -69,    // attempt to create an empty waveform
    PI_NO_WAVEFORM_ID = -70,    // no more waveforms
    PI_I2C_OPEN_FAILED = -71,   // can't open I2C device
    PI_SER_OPEN_FAILED = -72,   // can't open serial device
    PI_SPI_OPEN_FAILED = -73,   // can't open SPI device
    PI_BAD_I2C_BUS = -74,       // bad I2C bus
    PI_BAD_I2C_ADDR = -75,      // bad I2C address
    PI_BAD_SPI_CHANNEL = -76,   // bad SPI channel
    PI_BAD_FLAGS = -77,         // bad i2c/spi/ser open flags
    PI_BAD_SPI_SPEED = -78,     // bad SPI speed
    PI_BAD_SER_DEVICE = -79,    // bad serial device name
    PI_BAD_SER_SPEED = -80,     // bad serial baud rate
    PI_BAD_PARAM = -81,         // bad i2c/spi/ser parameter
    PI_I2C_WRITE_FAILED = -82,  // i2c write failed
    PI_I2C_READ_FAILED = -83,   // i2c read failed
    PI_BAD_SPI_COUNT = -84,     // bad SPI count
    PI_SER_WRITE_FAILED = -85,  // ser write failed
    PI_SER_READ_FAILED = -86,   // ser read failed
    PI_SER_READ_NO_DATA = -87,  // ser read no data available
    PI_UNKNOWN_COMMAND = -88,   // unknown command
    PI_SPI_XFER_FAILED = -89,   // spi xfer/read/write failed
    PI_BAD_POINTER = -90,       // bad (NULL) pointer
    PI_NO_AUX_SPI = -91,        // no auxiliary SPI on Pi A or B
    PI_NOT_PWM_GPIO = -92,      // GPIO is not in use for PWM
    PI_NOT_SERVO_GPIO = -93,    // GPIO is not in use for servo pulses
    PI_NOT_HCLK_GPIO = -94,     // GPIO has no hardware clock
    PI_NOT_HPWM_GPIO = -95,     // GPIO has no hardware PWM
    PI_BAD_HPWM_FREQ = -96,     // invalid hardware PWM frequency
    PI_BAD_HPWM_DUTY = -97,     // hardware PWM dutycycle not 0-1M
    PI_BAD_HCLK_FREQ = -98,     // invalid hardware clock frequency
    PI_BAD_HCLK_PASS = -99,     // need password to use hardware clock 1
    PI_HPWM_ILLEGAL = -100,     // illegal, PWM in use for main clock
    PI_BAD_DATABITS = -101,     // serial data bits not 1-32
    PI_BAD_STOPBITS = -102,     // serial (half) stop bits not 2-8
    PI_MSG_TOOBIG = -103,       // socket/pipe message too big
    PI_BAD_MALLOC_MODE = -104,  // bad memory allocation mode
    PI_TOO_MANY_SEGS = -105,    // too many I2C transaction segments
    PI_BAD_I2C_SEG = -106,      // an I2C transaction segment failed
    PI_BAD_SMBUS_CMD = -107,    // SMBus command not supported by driver
    PI_NOT_I2C_GPIO = -108,     // no bit bang I2C in progress on GPIO
    PI_BAD_I2C_WLEN = -109,     // bad I2C write length
    PI_BAD_I2C_RLEN = -110,     // bad I2C read length
    PI_BAD_I2C_CMD = -111,      // bad I2C command
    PI_BAD_I2C_BAUD = -112,     // bad I2C baud rate, not 50-500k
    PI_CHAIN_LOOP_CNT = -113,   // bad chain loop count
    PI_BAD_CHAIN_LOOP = -114,   // empty chain loop
    PI_CHAIN_COUNTER = -115,    // too many chain counters
    PI_BAD_CHAIN_CMD = -116,    // bad chain command
    PI_BAD_CHAIN_DELAY = -117,  // bad chain delay micros
    PI_CHAIN_NESTING = -118,    // chain counters nested too deeply
    PI_CHAIN_TOO_BIG = -119,    // chain is too long
    PI_DEPRECATED = -120,       // deprecated function removed
    PI_BAD_SER_INVERT = -121,   // bit bang serial invert not 0 or 1
    PI_BAD_EDGE = -122,         // bad ISR edge value, not 0-2
    PI_BAD_ISR_INIT = -123,     // bad ISR initialisation
    PI_BAD_FOREVER = -124,      // loop forever must be last command
    PI_BAD_FILTER = -125,       // bad filter parameter
    PI_BAD_PAD = -126,          // bad pad number
    PI_BAD_STRENGTH = -127,     // bad pad drive strength
    PI_FIL_OPEN_FAILED = -128,  // file open failed
    PI_BAD_FILE_MODE = -129,    // bad file mode
    PI_BAD_FILE_FLAG = -130,    // bad file flag
    PI_BAD_FILE_READ = -131,    // bad file read
    PI_BAD_FILE_WRITE = -132,   // bad file write
    PI_FILE_NOT_ROPEN = -133,   // file not open for read
    PI_FILE_NOT_WOPEN = -134,   // file not open for write
    PI_BAD_FILE_SEEK = -135,    // bad file seek
    PI_NO_FILE_MATCH = -136,    // no files match pattern
    PI_NO_FILE_ACCESS = -137,   // no permission to access file
    PI_FILE_IS_A_DIR = -138,    // file is a directory
    PI_BAD_SHELL_STATUS = -139, // bad shell return status
    PI_BAD_SCRIPT_NAME = -140,  // bad script name
    PI_BAD_SPI_BAUD = -141,     // bad SPI baud rate, not 50-500k
    PI_NOT_SPI_GPIO = -142,     // no bit bang SPI in progress on GPIO
    PI_BAD_EVENT_ID = -143,     // bad event id
    PI_CMD_INTERRUPTED = -144,  // Used by Python
    PI_NOT_ON_BCM2711 = -145,   // not available on BCM2711
    PI_ONLY_ON_BCM2711 = -146,  // only available on BCM2711
};

template <PigpioError... allowed_errors>
class BasicPigpioErrorView
{
private:
    const PigpioError _error;

    template <typename = void>
    bool _error_allowed() const
    {
        return false;
    }

    // This way, code to compare all allowed errors to the one that occurred is generated at compile time.
    // Source to make it work: https://stackoverflow.com/a/51000072
    template <PigpioError e, PigpioError... others>
    bool _error_allowed() const
    {
        return this->_error == e || this->_error_allowed<others...>();
    }

    bool is_error_allowed() const
    {
        return _error_allowed<allowed_errors...>();
    }

public:
    BasicPigpioErrorView(const PigpioError error)
        : _error(error)
    {
    }

    operator PigpioError() const
    {
        return this->is_error_allowed() ? this->_error : PigpioError::PI_UNEXPECTED_ERROR;
    }

    operator int() const
    {
        return static_cast<int>(static_cast<PigpioError>(*this));
    }

    PigpioError get_error() const
    {
        return this->_error;
    }
};

template <PigpioError... allowed_errors>
using PigpioErrorView = BasicPigpioErrorView<PigpioError::PI_OK,
                                             PigpioError::pigif_bad_send,
                                             PigpioError::pigif_bad_recv,
                                             PigpioError::pigif_unconnected_pi, allowed_errors...>;

template <typename return_value_t, typename error_t>
class PigpioResult
{
public:
    tl::optional<return_value_t> Value;
    error_t Error;

    PigpioResult(return_value_t value)
        : Value(value), Error(error_t(PigpioError::PI_OK))
    {
    }

    PigpioResult(PigpioError error)
        : Error(error_t(error))
    {
    }
};

#endif // __PIGPIOERROR_H__