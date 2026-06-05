const { getCurrentUVFromHourly } = require('./weather_openmeteo');

describe('getCurrentUVFromHourly', () => {
  const mockJson = {
    hourly: {
      time: [
        '2023-10-27T10:00',
        '2023-10-27T11:00',
        '2023-10-27T12:00',
        '2023-10-27T13:00',
      ],
      uv_index: [1.2, 2.5, 5.8, 4.1],
    },
  };

  test('should return the exact match when the time matches an hourly data point exactly', () => {
    // 11:00 corresponds to index 1 (value 2.5, rounds to 3)
    const now = new Date('2023-10-27T11:00');
    const result = getCurrentUVFromHourly(mockJson, now);
    expect(result).toBe(3); // Math.round(2.5)
  });

  test('should return the nearest past value when the time is slightly past an hourly data point', () => {
    // 11:15 is closest to 11:00 (index 1, value 2.5)
    const now = new Date('2023-10-27T11:15');
    const result = getCurrentUVFromHourly(mockJson, now);
    expect(result).toBe(3); // Math.round(2.5)
  });

  test('should return the nearest future value when the time is closer to the next hourly data point', () => {
    // 11:45 is closest to 12:00 (index 2, value 5.8)
    const now = new Date('2023-10-27T11:45');
    const result = getCurrentUVFromHourly(mockJson, now);
    expect(result).toBe(6); // Math.round(5.8)
  });

  test('should round the UV index properly', () => {
    // 10:00 (index 0, value 1.2 -> rounds to 1)
    const now = new Date('2023-10-27T10:00');
    const result = getCurrentUVFromHourly(mockJson, now);
    expect(result).toBe(1); // Math.round(1.2)
  });
});

describe('getWeatherFromCoords', () => {
  const { getWeatherFromCoords } = require('./weather_openmeteo');

  let consoleLogSpy;

  beforeEach(() => {
    // Suppress console.log statements from tests to keep output clean
    consoleLogSpy = jest.spyOn(console, 'log').mockImplementation(() => {});
  });

  afterEach(() => {
    consoleLogSpy.mockRestore();
  });

  test('should not throw when pos is undefined', () => {
    expect(() => getWeatherFromCoords()).not.toThrow();
  });

  test('should not throw when pos is null', () => {
    expect(() => getWeatherFromCoords(null)).not.toThrow();
  });

  test('should not throw when pos.coords is missing', () => {
    expect(() => getWeatherFromCoords({})).not.toThrow();
  });

  test('should not throw when pos.coords is null', () => {
    expect(() => getWeatherFromCoords({ coords: null })).not.toThrow();
  });

  test('should not throw when latitude or longitude is null', () => {
    expect(() => getWeatherFromCoords({ coords: { latitude: null, longitude: 10 } })).not.toThrow();
    expect(() => getWeatherFromCoords({ coords: { latitude: 10, longitude: null } })).not.toThrow();
  });

  test('should log "Invalid coordinates provided." when coordinates are invalid', () => {
    getWeatherFromCoords(null);
    expect(consoleLogSpy).toHaveBeenCalledWith('Invalid coordinates provided.');
  });

  test('should call weatherCommon.xhrRequest when valid coordinates are provided', () => {
    const weatherCommon = require('./weather');
    const xhrRequestSpy = jest.spyOn(weatherCommon, 'xhrRequest').mockImplementation(() => {});

    getWeatherFromCoords({ coords: { latitude: 40.7128, longitude: -74.0060 } });

    expect(xhrRequestSpy).toHaveBeenCalledTimes(1);
    const expectedUrlPart = 'latitude=40.7128&longitude=-74.006';
    expect(xhrRequestSpy.mock.calls[0][0]).toContain(expectedUrlPart);
    expect(xhrRequestSpy.mock.calls[0][1]).toBe('GET');

    xhrRequestSpy.mockRestore();
  });
});

describe('getIconForWeatherCode', () => {
  const { getIconForWeatherCode } = require('./weather_openmeteo');
  const weatherCommon = require('./weather');
  const icons = weatherCommon.icons;

  test('should return correct icon for clear day and night', () => {
    expect(getIconForWeatherCode(0, false)).toBe(icons.CLEAR_DAY);
    expect(getIconForWeatherCode(0, true)).toBe(icons.CLEAR_NIGHT);
  });

  test('should return correct icon for partly cloudy day and night', () => {
    expect(getIconForWeatherCode(1, false)).toBe(icons.PARTLY_CLOUDY);
    expect(getIconForWeatherCode(1, true)).toBe(icons.PARTLY_CLOUDY_NIGHT);
    expect(getIconForWeatherCode(2, false)).toBe(icons.PARTLY_CLOUDY);
    expect(getIconForWeatherCode(2, true)).toBe(icons.PARTLY_CLOUDY_NIGHT);
  });

  test('should return correct icon for cloudy conditions', () => {
    expect(getIconForWeatherCode(3)).toBe(icons.CLOUDY_DAY);
    expect(getIconForWeatherCode(45)).toBe(icons.CLOUDY_DAY);
    expect(getIconForWeatherCode(48)).toBe(icons.CLOUDY_DAY);
  });

  test('should return correct icon for light rain conditions', () => {
    expect(getIconForWeatherCode(51)).toBe(icons.LIGHT_RAIN);
    expect(getIconForWeatherCode(53)).toBe(icons.LIGHT_RAIN);
    expect(getIconForWeatherCode(55)).toBe(icons.LIGHT_RAIN);
    expect(getIconForWeatherCode(61)).toBe(icons.LIGHT_RAIN);
    expect(getIconForWeatherCode(80)).toBe(icons.LIGHT_RAIN);
  });

  test('should return correct icon for heavy rain conditions', () => {
    expect(getIconForWeatherCode(63)).toBe(icons.HEAVY_RAIN);
    expect(getIconForWeatherCode(65)).toBe(icons.HEAVY_RAIN);
    expect(getIconForWeatherCode(81)).toBe(icons.HEAVY_RAIN);
    expect(getIconForWeatherCode(82)).toBe(icons.HEAVY_RAIN);
  });

  test('should return correct icon for raining and snowing conditions', () => {
    expect(getIconForWeatherCode(56)).toBe(icons.RAINING_AND_SNOWING);
    expect(getIconForWeatherCode(57)).toBe(icons.RAINING_AND_SNOWING);
    expect(getIconForWeatherCode(66)).toBe(icons.RAINING_AND_SNOWING);
    expect(getIconForWeatherCode(67)).toBe(icons.RAINING_AND_SNOWING);
  });

  test('should return correct icon for light snow conditions', () => {
    expect(getIconForWeatherCode(71)).toBe(icons.LIGHT_SNOW);
    expect(getIconForWeatherCode(77)).toBe(icons.LIGHT_SNOW);
    expect(getIconForWeatherCode(85)).toBe(icons.LIGHT_SNOW);
  });

  test('should return correct icon for heavy snow conditions', () => {
    expect(getIconForWeatherCode(73)).toBe(icons.HEAVY_SNOW);
    expect(getIconForWeatherCode(75)).toBe(icons.HEAVY_SNOW);
    expect(getIconForWeatherCode(86)).toBe(icons.HEAVY_SNOW);
  });

  test('should return correct icon for thunderstorm conditions', () => {
    expect(getIconForWeatherCode(95)).toBe(icons.THUNDERSTORM);
    expect(getIconForWeatherCode(96)).toBe(icons.THUNDERSTORM);
    expect(getIconForWeatherCode(99)).toBe(icons.THUNDERSTORM);
  });

  test('should return generic weather icon for unknown conditions', () => {
    expect(getIconForWeatherCode(-1)).toBe(icons.WEATHER_GENERIC);
    expect(getIconForWeatherCode(999)).toBe(icons.WEATHER_GENERIC);
    expect(getIconForWeatherCode(null)).toBe(icons.WEATHER_GENERIC);
    expect(getIconForWeatherCode(undefined)).toBe(icons.WEATHER_GENERIC);
  });
});
