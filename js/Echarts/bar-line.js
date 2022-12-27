function op(num) {
  return 54 * num;
}

function op2(num) {
  return 0.1 * num;
}

option = {
  tooltip: {
    trigger: 'axis',
    axisPointer: {
      type: 'cross',
      crossStyle: {
        color: '#999'
      }
    },
    
  },
  toolbox: {
    feature: {
      dataView: { show: true, readOnly: false },
      magicType: { show: true, type: ['line', 'bar'] },
      restore: { show: true },
      saveAsImage: { show: true }
    }
  },
  legend: {
    data: ['绿色信贷余额', '绿色信贷余额同比增长']
  },
  xAxis: [
    {
      axisLabel: {rotate:45},
      type: 'category',
      data: [
        '2018-12-31', 
      '2019-3-31', 
      '2019-6-30', 
      '2019-9-30',
      '2019-12-31', 
      '2020-3-31', 
      '2020-6-30',
      '2020-9-30',
      '2020-12-31',
      '2021-3-31',
      '2021-6-30',
      '2021-9-30',
      '2021-12-31',
      '2022-3-31',
      '2022-6-30',
      '2022-9-30'
      ],
      axisPointer: {
        type: 'shadow'
      }
    }
  ],
  yAxis: [
    {
      axisTick: {show: false},
      axisLine: {show: false},
      splitLine: {show: false},
      type: 'value',
      name: '',
      min: 0,
      max: 25000,
      //interval: 50,
      axisLabel: {
        formatter: '{value}'
      }
    },
    {
      axisTick: {show: false},
      axisLine: {show: false},
      splitLine: {show: false},
      type: 'value',
      name: '',
      min: 0,
      max: 45,
      //interval: 50,
      axisLabel: {
        formatter: '{value}'
      }
    }
  ],
  series: [
    {
      color:'red',
      name: '绿色信贷余额',
      type: 'bar',
      tooltip: {
        valueFormatter: function (value) {
          return value;
        }
      },
      data: [
        141,
        163,
        166,
        174,
        180,
        185,
        195,
        204,
        210,
        230,
        245,
        261,
        281,
        319,
        346,
        370
      ].map(op)
    },
    {
      name: '绿色信贷余额同比增长',
      type: 'line',
      yAxisIndex: 1,
      tooltip: {
        valueFormatter: function (value) {
          return value;
        }
      },
      data: [
        160,
        46,
        68,
        111,
        147,
        56,
        106,
        159,
        200,
        242,
        264,
        279,
        328,
        379,
        401,
        409].map(op2)
    }
  ]
};
