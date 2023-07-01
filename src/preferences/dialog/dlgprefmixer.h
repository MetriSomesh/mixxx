#pragma once

#include "control/controlproxy.h"
#include "control/pollingcontrolproxy.h"
#include "effects/effectsmanager.h"
#include "preferences/dialog/dlgpreferencepage.h"
#include "preferences/dialog/ui_dlgprefmixerdlg.h"
#include "preferences/usersettings.h"

class DlgPrefMixer : public DlgPreferencePage, public Ui::DlgPrefMixerDlg {
    Q_OBJECT
  public:
    DlgPrefMixer(
            QWidget* parent,
            std::shared_ptr<EffectsManager> pEffectsManager,
            UserSettingsPointer _config);
    virtual ~DlgPrefMixer();

    QUrl helpUrl() const override;

  public slots:
    void slotApply() override;
    void slotUpdate() override;
    void slotResetToDefaults() override;

  private slots:
    void slotNumDecksChanged(double numDecks);
    void slotEQEffectChangedOnDeck(int effectIndex);
    void slotQuickEffectChangedOnDeck(int effectIndex);
    void slotEqOnlyToggled(bool checked);
    void slotSingleEqToggled(bool checked);
    void slotEqAutoResetToggled(bool checked);
    void slotGainAutoResetToggled(bool checked);
    void slotBypassEqToggled(bool checked);
    // Create, populate and show/hide EQ & QuickEffect selectors, considering the
    // number of decks and the 'Single EQ' checkbox
    void slotPopulateDeckEqSelectors();
    void slotPopulateQuickEffectSelectors();

    void slotUpdateXFader();
    void slotHiEqSliderChanged();
    void slotLoEqSliderChanged();

    void slotInstantMainEQToggled(bool checked);

    // Update the Main EQ
    void slotMainEQParameterSliderChanged(int value);
    void slotMainEQToDefault();
    void slotMainEqEffectChanged(int effectIndex);

  private:
    void drawXfaderDisplay();

    void setDefaultShelves();
    double getEqFreq(int value, int minimum, int maximum);
    int getSliderPosition(double eqFreq, int minimum, int maximum);
    void validateEQShelves();

    void applyDeckEQs();
    void applyQuickEffects();

    void applyEQShelves();

    void setUpMainEQ();
    void updateMainEQ();
    void applyMainEQ();
    void applyMainEqParameter(int index);

    typedef bool (*EffectManifestFilterFnc)(EffectManifest* pManifest);
    const QList<EffectManifestPointer> getDeckEqManifests() const;
    const QList<EffectManifestPointer> getMainEqManifests() const;

    UserSettingsPointer m_pConfig;

    // X-fader values
    int m_xFaderMode;
    double m_transform, m_cal;

    PollingControlProxy m_mode;
    PollingControlProxy m_curve;
    PollingControlProxy m_calibration;
    PollingControlProxy m_reverse;
    PollingControlProxy m_crossfader;

    bool m_xFaderReverse;

    PollingControlProxy m_COLoFreq;
    PollingControlProxy m_COHiFreq;
    double m_lowEqFreq, m_highEqFreq;

    EffectChainPresetManagerPointer m_pChainPresetManager;
    std::shared_ptr<EffectsManager> m_pEffectsManager;
    EffectsBackendManagerPointer m_pBackendManager;
    QList<QComboBox*> m_deckEqEffectSelectors;
    QList<QComboBox*> m_deckQuickEffectSelectors;
    ControlProxy* m_pNumDecks;

    bool m_ignoreEqQuickEffectBoxSignals;

    // Members needed for the Main EQ
    QList<QSlider*> m_mainEQSliders;
    QList<QLabel*> m_mainEQValues;
    QList<QLabel*> m_mainEQLabels;
    QWeakPointer<EffectSlot> m_pEffectMainEQ;

    bool m_singleEq;
    bool m_eqEffectsOnly;
    bool m_eqAutoReset;
    bool m_gainAutoReset;
    bool m_eqBypass;
    bool m_instantMainEq;

    bool m_initializing;

    QList<int> m_eqIndiciesOnUpdate;
    QList<int> m_quickEffectIndiciesOnUpdate;
};
