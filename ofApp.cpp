#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->frame_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->face_mesh.clear();
	this->frame_mesh.clear();

	int len = 100;
	ofColor color;
	for (int i = 0; i < 100; i++) {

		int seed_z = ofRandom(len * 0.5);
		int seed_param = i;
		int step_z = 1;
		int step_param = 1;
		int start_index = this->face_mesh.getNumVertices();
		bool break_flag = true;
		color.setHsb(ofRandom(255), 180, 255);
		for (int k = 0; k < 25; k++) {

			int z = (int)(seed_z + ofGetFrameNum() + k * step_z) % len - len * 0.5;
			if (z <= -245 || z >= 245) {

				break_flag = false;
				break;
			}
			int upper_z = z + step_z;

			int param = (seed_param + ofGetFrameNum() + k * step_param) % 100;
			int next_param = param + step_param;

			auto index = this->face_mesh.getVertices().size();
			vector<glm::vec3> vertices = {
				glm::vec3(this->make_point(len, param), z),
				glm::vec3(this->make_point(len, param), upper_z),
				glm::vec3(this->make_point(len, next_param), upper_z),
				glm::vec3(this->make_point(len, next_param), upper_z + step_z)
			};

			this->face_mesh.addVertices(vertices);
			this->frame_mesh.addVertices(vertices);

			this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 1); this->face_mesh.addIndex(index + 3);
			this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 2); this->face_mesh.addIndex(index + 3);

			this->frame_mesh.addIndex(index + 0); this->frame_mesh.addIndex(index + 2);
			this->frame_mesh.addIndex(index + 1); this->frame_mesh.addIndex(index + 3);
		}

		this->frame_mesh.addIndex(start_index + 0); this->frame_mesh.addIndex(start_index + 1);
		this->frame_mesh.addIndex(this->frame_mesh.getNumVertices() - 1); this->frame_mesh.addIndex(this->frame_mesh.getNumVertices() - 2);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);

	ofSetColor(239);
	this->face_mesh.drawFaces();

	ofSetColor(39);
	this->frame_mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}