
-- SUMMARY --

The Dibs module extends the functionality of the Plus1 voting module.
The term Dibs implies wanting something that someone else has posted, and 
asking to be placed in consideraion.  Dibs management allows the posting party
to review the list of those requesting consideration and elect one requestor.

The Plus1 modification is that instead of just adding a Thumbs Up or Plus 1, 
Dibs regesters a user's request, and adds a tab to the /user page listing the
requestor's interests.  Dibs management is for the posting party and adds a tab
to their /user page with a list of interested parties.

For a full description of the module, visit the project page:
  http://github.com/willisiw/drupal-vote-dibs-module

To submit bug reports and feature suggestions, or to track changes:
  http://github.com/willisiw/drupal-vote-dibs-module/issues


-- REQUIREMENTS --

* Voting API   http://drupal.org/project/votingapi
* Plus1        http://drupal.org/project/plus1


-- INSTALLATION --

* Make sure Plus1 and Voting API are installed and enabled.

* Configure Plus1.

* Install Dibs module using the zip file.  For further info visit 
  http://drupal.org/documentation/install/modules-themes/modules-7

-- CONFIGURATION --

* Configure Plus1 at ?q=admin/config/user-interface/plus1 

Plus1 key settings:
 * Select Content Types that will show the dibs option
 * Change the "Vote Text" to "Call Dibs"
 * Change the "Feedback provided to voter when he already voted" text
   to "Called Dibs" or "Got Dibs" or simply "Dibs!"
 * Check "Allow users to undo their node votes"
 * Leave "Feedback provided to voter when he already voted and user 
   CAN undo his vote" text blank
 
* Dibs requires no config.  The dibs module only alters the +1 module, and adds
  tabs to ?q=user to manage the exchanging of dibs.


-- TROUBLESHOOTING --


-- FAQ --


-- CONTACT --

Current maintainers:
* Ian Willis (willisiw) - http://github.com/willisiw

