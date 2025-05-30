/*
 * Copyright 2019 NXP
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

using Rg.Plugins.Popup.Pages;
using Rg.Plugins.Popup.Services;
using System;
using System.ComponentModel;
using System.Threading.Tasks;
using Xamarin.Forms;
using Xamarin.Forms.Xaml;

namespace TLogger.Popups
{
    [XamlCompilation(XamlCompilationOptions.Compile)]
    public partial class ConfigParamsPopup : PopupPage
    {
        Msg.Lib _msgLib;

        Msg.Models.MeasurementConfigModel.CConfig _measurementConfig = new Msg.Models.MeasurementConfigModel.CConfig();
        Msg.Models.TemperatureConfigModel.CConfig _temperatureConfig = new Msg.Models.TemperatureConfigModel.CConfig();

        public ConfigParamsPopup()
        {
            InitializeComponent ();

            _msgLib = App.MsgLib;

            if (_msgLib.MeasurementStatusModel.Status.Measurement == Msg.Models.MeasurementStatusModel.Measurement.Reset ||
                _msgLib.MeasurementStatusModel.Status.Measurement == Msg.Models.MeasurementStatusModel.Measurement.Unknown ||
                _msgLib.MeasurementStatusModel.Status.Measurement == Msg.Models.MeasurementStatusModel.Measurement.NotConfigured)
            {
                MeasurementStartupDelay = TimeSpan.FromSeconds(10);
                MeasurementInterval = TimeSpan.FromSeconds(15);
                MeasurementDuration = TimeSpan.Zero;
                TemperatureLimitMin = 20;
                TemperatureLimitMax = 35;

                _measurementConfig.StartupDelay = MeasurementStartupDelay;
                _measurementConfig.Interval = MeasurementInterval;
                _measurementConfig.Duration = MeasurementDuration;

                _temperatureConfig.ConfiguredMin = TemperatureLimitMin;
                _temperatureConfig.ConfiguredMax = TemperatureLimitMax;
            }
            else
            {
                MeasurementStartupDelay = _msgLib.MeasurementConfigModel.Config.StartupDelay;
                MeasurementInterval = _msgLib.MeasurementConfigModel.Config.Interval;
                MeasurementDuration = _msgLib.MeasurementConfigModel.Config.Duration;
                TemperatureLimitMin = (int)_msgLib.TemperatureConfigModel.Config.ConfiguredMin;
                TemperatureLimitMax = (int)_msgLib.TemperatureConfigModel.Config.ConfiguredMax;

                _measurementConfig.StartupDelay = _msgLib.MeasurementConfigModel.Config.StartupDelay;
                _measurementConfig.Interval = _msgLib.MeasurementConfigModel.Config.Interval;
                _measurementConfig.Duration = _msgLib.MeasurementConfigModel.Config.Duration;
                _temperatureConfig.ConfiguredMin = (int)_msgLib.TemperatureConfigModel.Config.ConfiguredMin;
                _temperatureConfig.ConfiguredMax = (int)_msgLib.TemperatureConfigModel.Config.ConfiguredMax;
            }
        }

        string _measurementStartupDelayText;
        public string MeasurementStartupDelayText
        {
            get => _measurementStartupDelayText;
            set => Device.BeginInvokeOnMainThread(() =>
            {
                _measurementStartupDelayText = measurementStartupDelay.Text = value;
            });
        }

        string _measurementIntervalText;
        public string MeasurementIntervalText
        {
            get => _measurementIntervalText;
            set => Device.BeginInvokeOnMainThread(() =>
            {
                _measurementIntervalText = measurementInterval.Text = value;
            });
        }

        string _measurementDurationText;
        public string MeasurementDurationText
        {
            get => _measurementDurationText;
            set => Device.BeginInvokeOnMainThread(() =>
            {
                _measurementDurationText = measurementDuration.Text = value;
            });
        }

        string _temperatureLimitsText;
        public string TemperatureLimitsText
        {
            get => _temperatureLimitsText;
            set => Device.BeginInvokeOnMainThread(() =>
            {
                _temperatureLimitsText = temperatureLimits.Text = value;
            });
        }

        TimeSpan _measurementStartupDelay;
        public TimeSpan MeasurementStartupDelay
        {
            get => _measurementStartupDelay;
            set
            {
                _measurementStartupDelay = value;
                if (_measurementStartupDelay == TimeSpan.Zero)
                    MeasurementStartupDelayText = "Start measurements immediately";
                else
                    MeasurementStartupDelayText =
                        "Wait " +
                        Helpers.TimeSpanHelper.ReadableTimeSpan(_measurementStartupDelay, 2) +
                        " before measurements start";
            }

        }

        TimeSpan _measurementInterval;
        public TimeSpan MeasurementInterval
        {
            get => _measurementInterval;
            set
            {
                _measurementInterval = value;
                MeasurementIntervalText =
                    "Measure every " +
                    Helpers.TimeSpanHelper.ReadableTimeSpan(_measurementInterval, 2);
            }
        }

        TimeSpan _measurementDuration;
        public TimeSpan MeasurementDuration
        {
            get => _measurementDuration;
            set
            {
                _measurementDuration = value;
                if (_measurementDuration == TimeSpan.Zero)
                    MeasurementDurationText = "Keep measuring until storage is full";
                else
                    MeasurementDurationText =
                        " Keep measuring " +
                        Helpers.TimeSpanHelper.ReadableTimeSpan(_measurementDuration, 2) +
                        " and power-off";
            }
        }

        int _temperatureLimitMin;
        public int TemperatureLimitMin
        {
            get => _temperatureLimitMin;
            set
            {
                _temperatureLimitMin = value;
                TemperatureLimitsText =
                    "Temperature should be between " +
                    _temperatureLimitMin.ToString() + "\u00b0C " +
                    "and " +
                    _temperatureLimitMax.ToString() + "\u00b0C";
            }
        }

        int _temperatureLimitMax;
        public int TemperatureLimitMax
        {
            get => _temperatureLimitMax;
            set
            {
                _temperatureLimitMax = value;
                TemperatureLimitsText =
                    "Desired temperature is above " +
                    _temperatureLimitMin.ToString() + "\u00b0C " +
                    "and below " +
                    _temperatureLimitMax.ToString() + "\u00b0C";
            }
        }

        async void OnMeasurementStartupDelay(object sender, EventArgs e)
        {
            try
            {
                var tcs = new TaskCompletionSource<Popups.MeasurementStartupDelayPopup.SMeasurementStartupDelay>();
                await Rg.Plugins.Popup.Services.PopupNavigation.Instance.PushAsync(
                    new Popups.MeasurementStartupDelayPopup(MeasurementStartupDelay, tcs));

                await tcs.Task.ContinueWith(measurementStartupDelay =>
                {
                    if (measurementStartupDelay.IsCompleted)
                    {
                        if (measurementStartupDelay.Result.isOk)
                        {
                            MeasurementStartupDelay = measurementStartupDelay.Result.timeSpan;
                            _measurementConfig.StartupDelay = measurementStartupDelay.Result.timeSpan;
                        }
                    }
                });
            }
            catch (Exception ex)
            {
                Helpers.ExceptionLogHelper.Log(_msgLib.TagModel.TagId, ex.Message);
            }
        }

        async void OnMeasurementInterval(object sender, EventArgs e)
        {
            try
            {
                var tcs = new TaskCompletionSource<Popups.MeasurementIntervalPopup.SMeasurementInterval>();
                await Rg.Plugins.Popup.Services.PopupNavigation.Instance.PushAsync(
                    new Popups.MeasurementIntervalPopup(MeasurementInterval, tcs));

                await tcs.Task.ContinueWith(measurementInterval =>
                {
                    if (measurementInterval.IsCompleted)
                    {
                        if (measurementInterval.Result.isOk)
                        {
                            MeasurementInterval = measurementInterval.Result.timeSpan;
                            _measurementConfig.Interval = measurementInterval.Result.timeSpan;
                        }
                    }
                });
            }
            catch (Exception ex)
            {
                Helpers.ExceptionLogHelper.Log(_msgLib.TagModel.TagId, ex.Message);
            }
        }

        async void OnMeasurementDuration(object sender, EventArgs e)
        {
            try
            {
                var tcs = new TaskCompletionSource<Popups.MeasurementDurationPopup.SMeasurementDuration>();
                await Rg.Plugins.Popup.Services.PopupNavigation.Instance.PushAsync(
                    new Popups.MeasurementDurationPopup(MeasurementDuration, tcs));

                await tcs.Task.ContinueWith(measurementDuration =>
                {
                    if (measurementDuration.IsCompleted)
                    {
                        if (measurementDuration.Result.isOk)
                        {
                            MeasurementDuration = measurementDuration.Result.timeSpan;
                            _measurementConfig.Duration = measurementDuration.Result.timeSpan;
                        }
                    }
                });
            }
            catch (Exception ex)
            {
                Helpers.ExceptionLogHelper.Log(_msgLib.TagModel.TagId, ex.Message);
            }
        }

        async void OnTemperatureLimits(object sender, EventArgs e)
        {
            try
            {
                var tcs = new TaskCompletionSource<Popups.TemperatureLimitsPopup.STemperatureLimits>();
                await Rg.Plugins.Popup.Services.PopupNavigation.Instance.PushAsync(
                    new Popups.TemperatureLimitsPopup(
                        TemperatureLimitMin,
                        TemperatureLimitMax,
                        "°C",
                        tcs));

                await tcs.Task.ContinueWith(temperatureLimits =>
                {
                    if (temperatureLimits.IsCompleted)
                    {
                        if (temperatureLimits.Result.isOk)
                        {
                            TemperatureLimitMin = temperatureLimits.Result.min;
                            TemperatureLimitMax = temperatureLimits.Result.max;
                            _temperatureConfig.ConfiguredMin = temperatureLimits.Result.min;
                            _temperatureConfig.ConfiguredMax = temperatureLimits.Result.max;
                        }
                    }
                });
            }
            catch (Exception ex)
            {
                Helpers.ExceptionLogHelper.Log(_msgLib.TagModel.TagId, ex.Message);
            }
        }

        async void OnSetConfiguration(object sender, EventArgs e)
        {
            _measurementConfig.CurrentTime = DateTime.UtcNow;

            await Rg.Plugins.Popup.Services.PopupNavigation.Instance.PushAsync(
                new Popups.SetConfigPopup(
                    false,
                    _measurementConfig,
                    _temperatureConfig));
        }

        async void OnResetTag(object sender, EventArgs e)
        {
            var measurementConfig = new Msg.Models.MeasurementConfigModel.CConfig()
            {
                CurrentTime = new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc),
                StartupDelay = TimeSpan.FromSeconds(0),
                Interval = TimeSpan.FromSeconds(0),
                Duration = TimeSpan.FromSeconds(0),
            };

            await Rg.Plugins.Popup.Services.PopupNavigation.Instance.PushAsync(
                new Popups.SetConfigPopup(
                    true,
                    measurementConfig,
                    new Msg.Models.TemperatureConfigModel.CConfig()));
        }

        protected override bool OnBackgroundClicked()
        {
            return false; 
        }

        protected override void OnDisappearing()
        {
            base.OnDisappearing();
        }

        async void OnOkButton(object sender, EventArgs e)
        {
             await Rg.Plugins.Popup.Services.PopupNavigation.Instance.PopAsync(true);
        }

    }
}
