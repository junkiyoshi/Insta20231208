#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetCircleResolution(60);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	auto radius = 35;
	vector<glm::vec2> base_location;
	for (int deg = 0; deg < 360; deg += 45) {

		base_location.push_back(glm::vec2(300 * cos(deg * DEG_TO_RAD), 300 * sin(deg * DEG_TO_RAD)));
		base_location.push_back(glm::vec2(150 * cos(deg * DEG_TO_RAD), 150 * sin(deg * DEG_TO_RAD)));
	}
	
	for (int i = 0; i < base_location.size(); i++) {

		auto deg_param = ofMap(ofNoise(base_location[i].x, base_location[i].y, ofGetFrameNum() * 0.01), 0, 1, -360, 360);
		auto next_deg_param = ofMap(ofNoise(
			base_location[(i + 1) % base_location.size()].x, base_location[(i + 1) % base_location.size()].y, ofGetFrameNum() * 0.01), 0, 1, -360, 360);

		ofColor color;
		ofFill();
		for (int deg = 0; deg < 90; deg += 10) {

			auto location_1 = base_location[i] + glm::vec2(radius * cos((deg + deg_param) * DEG_TO_RAD), radius * sin((deg + deg_param) * DEG_TO_RAD));
			auto location_2 = base_location[(i + 1) % base_location.size()] + glm::vec2(radius * cos((deg + next_deg_param) * DEG_TO_RAD), radius * sin((deg + next_deg_param) * DEG_TO_RAD));

			color.setHsb(ofMap(deg, 0, 90, 0, 255), 180, 255);
			ofSetColor(color);

			ofDrawCircle(location_1, 2.5);
			ofDrawLine(location_1, location_2);
		}

		ofNoFill();
		ofSetColor(255);
		ofDrawCircle(base_location[i], 25);
	}

	/*
	int start = 150;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}