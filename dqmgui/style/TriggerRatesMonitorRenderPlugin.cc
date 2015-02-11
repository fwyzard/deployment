#include <cmath>

#include <TProfile2D.h>
#include <TProfile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TColor.h>
#include <TText.h>

#include "DQM/DQMRenderPlugin.h"
#include "utils.h"

class TriggerRatesMonitorRenderPlugin : public DQMRenderPlugin {

public:
  virtual bool applies(const VisDQMObject &o, const VisDQMImgInfo &) {

    if (o.name.find("HLT/TriggerRates") == 0)
      return true;

    return false;

  }

  virtual void preDraw(TCanvas *, const VisDQMObject & , const VisDQMImgInfo &, VisDQMRenderInfo &) {
  }

  virtual void postDraw(TCanvas * c, const VisDQMObject & o, const VisDQMImgInfo & i) {
    customiseLumisectionRange(c, o, i);
  }

private:

  /*
  void customiseTH1F(TCanvas * c, const VisDQMObject & o, const VisDQMImgInfo &) {
    // is this needed ?
    c->cd();

    TH1F * obj = dynamic_cast<TH1F *>(o.object);
    // this is supposed to be a TH1F
    if (not obj)
      return;

    // disable statistics panel, draw as a histogram, set black line color
    obj->SetStats(false);
    obj->SetDrawOption("H");
    obj->SetLineColor(kBlack);

    // make a copy and draw red Y error bars
    TH1F * copy = (TH1F *) obj->DrawCopy("SAME E1 X0");
    copy->SetLineColor(kRed);
  }
  */

  void customiseLumisectionRange(TCanvas * c, const VisDQMObject & o, const VisDQMImgInfo & i) {
    // is this needed ?
    c->cd();

    TH1 * obj = dynamic_cast<TH1 *>(o.object);
    // this is supposed to be a TH1 or derived object
    if (not obj)
      return;

    // if the maximum is not specified, find maximum filled bin
    if (std::isnan(i.xaxis.max)) {
      int xmax = 0;
      for (int i = 1; i <= obj->GetNbinsX(); ++i)
        if (obj->GetBinContent(i))
          xmax = i;
      TAxis * a = obj->GetXaxis();
      a->SetRange(a->GetFirst(), xmax);
    }
  }

};

static TriggerRatesMonitorRenderPlugin instance;
