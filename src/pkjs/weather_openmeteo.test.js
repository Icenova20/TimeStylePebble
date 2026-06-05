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
