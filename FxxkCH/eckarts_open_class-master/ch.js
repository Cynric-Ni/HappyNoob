(function () {
  // 1实例化对象
  var myChart = echarts.init(document.querySelector(".bar1 .chart"));
  // 2. 指定配置项和数据
  var option = {
    tooltip: {
      trigger: "axis",
      axisPointer: {
        // Use axis to trigger tooltip
        type: "shadow", // 'shadow' as default; can also be 'line' or 'shadow'
      },
    },
    //麻痹的这个是类别
    legend: {
      date: ["优", "良", "中", "差"],
      textStyle: {
        color: "rgba(255,255,255,.6)",
      },
    },
    grid: {
      left: "0%",
      right: "0%",
      bottom: "3%",
      containLabel: true,
    },
    textStyle: {
      color: "rgba(255,255,255,.6)",
      fontSize: "15",
    },
    xAxis: {
      type: "category",
      /* axisLabel: {
          textStyle: {
            color: "rgba(255,255,255,.6)", // 更改x轴文字颜色为红色
            fontSize: "15",
          },
        }, */
      data: ["大沙", "金口", "簰洲", "武汉", "阳逻", "黄冈", "黄石", "蕲州"],
    },
    yAxis: {
      type: "value",
    },
    series: [
      {
        name: "优",
        type: "bar",
        stack: "total",
        label: {
          show: true,
        },
        emphasis: {
          focus: "series",
        },
        data: [10, 20, 30, 40, 50, 60, 70, 80],
      },
      {
        name: "良",
        type: "bar",
        stack: "total",
        label: {
          show: true,
        },
        emphasis: {
          label: {
            color: "rgba(255,255,255,.6)",
          },
          focus: "series",
        },
        data: [10, 20, 30, 40, 50, 60, 70, 80],
      },
      {
        name: "中",
        type: "bar",
        stack: "total",
        label: {
          show: true,
        },
        emphasis: {
          focus: "series",
        },
        data: [10, 20, 30, 40, 50, 60, 70, 80],
      },
      {
        name: "差",
        type: "bar",
        stack: "total",
        label: {
          show: true,
        },
        emphasis: {
          focus: "series",
        },
        data: [10, 20, 30, 40, 50, 60, 70, 80],
      },
    ],
  };
  // 3. 把配置项给实例对象
  myChart.setOption(option);
  // 4. 让图表跟随屏幕自动的去适应
  window.addEventListener("resize", function () {
    myChart.resize();
  });
})();
